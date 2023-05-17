#include <iostream>
#include <vector>
#include <thread>
using namespace std;

struct Job
{
  string name; // 作业名
  int progress = 0; // 进展
  int demand; // 作业需求
  Job(string name, int demand) : name(name), demand(demand) {}
};

Job *cjob = nullptr; // 占用临界资源的当前作业
vector<Job *> waiting; // 作业等待队列
auto locked = false; // 资源锁

void lock() { locked = true; }
void unlock() { locked = false; }

void printWaiting() {
  for (auto j : waiting) cout << j->name << " ";
  cout << endl;
}

void action() { // 占用临界资源的行为
  while (true) {
    if (cjob != nullptr) {
      while (cjob->progress < cjob->demand) {
        while (locked);
        lock();
        this_thread::sleep_for(chrono::seconds(1));
        cjob->progress++;
        cout << "Job " << cjob->name << " is working: " << cjob->progress << "/" << cjob->demand << endl;
        unlock();
      }
      while (locked);
      lock();
      cout << "Job " << cjob->name << " finished." << endl;
      cjob = nullptr;
      unlock();
    } else if (!waiting.empty()) {
      while (locked);
      lock();
      cjob = waiting.front();
      waiting.erase(waiting.begin());
      cout << "Job " << cjob->name << " started." << endl;
      unlock();
    }
  }
}

void join(Job *job) {
  auto flag = true;
  for (auto iter = waiting.begin(); iter != waiting.end(); iter++) {
    if (job->demand < (*iter)->demand) {
      waiting.insert(iter, job);
      flag = false;
      break;
    }
  }
  if (flag) waiting.push_back(job);
  // printWaiting();
}

void arrive(Job *job) { // 作业到达
  while (locked);
  lock();
  cout << "Job " << job->name << " arrived." << endl;
  if (cjob == nullptr) join(job);
  else if (job->demand < cjob->demand) {
    cout << "Job " << job->name << "'s demand is lower than Job " << cjob->name << ", so Job " << cjob->name << " paused and Job " << job->name << " started." << endl;
    join(cjob);
    cjob = job;
  } else join(job);
  unlock();
}

int main() {
  thread p(action);
  arrive(new Job("A", 8));
  this_thread::sleep_for(chrono::seconds(1));
  arrive(new Job("B", 4));
  this_thread::sleep_for(chrono::seconds(1));
  arrive(new Job("C", 9));
  this_thread::sleep_for(chrono::seconds(1));
  arrive(new Job("D", 5));
  p.join();
  return 0;
}
