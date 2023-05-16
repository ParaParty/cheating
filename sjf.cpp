#include <iostream>
#include <vector>
#include <thread>
using namespace std;

struct Job
{
  string name; // ��ҵ��
  int progress = 0; // ��չ
  int demand; // ��ҵ����
  Job(string name, int demand) : name(name), demand(demand) {}
};

Job *cjob = nullptr; // ռ���ٽ���Դ�ĵ�ǰ��ҵ
vector<Job *> waiting; // ��ҵ�ȴ�����

void action() { // ռ���ٽ���Դ����Ϊ
  while (true) {
    if (cjob != nullptr) {
      while (cjob->progress < cjob->demand) {
        this_thread::sleep_for(chrono::seconds(1));
        cjob->progress++;
        cout << "Job " << cjob->name << " is working: " << cjob->progress << "/" << cjob->demand << endl;
      }
      cout << "Job " << cjob->name << " finished." << endl;
      cjob = nullptr;
    } else if (!waiting.empty()) {
      cjob = waiting.front();
      waiting.erase(waiting.begin());
      cout << "Job " << cjob->name << " started." << endl;
    }
  }
}

void join(Job *job) {
  if (waiting.empty()) waiting.push_back(job);
  for (auto iter = waiting.begin(); iter != waiting.end(); iter++) {
    if (job->demand < (*iter)->demand) {
      waiting.insert(iter, job);
      break;
    }
  }
}

void arrive(Job *job) { // ��ҵ����
  cout << "Job " << job->name << " arrived." << endl;
  if (cjob == nullptr) join(job);
  else if (job->demand < cjob->demand) {
    cout << "Job " << job->name << "'s demand is lower than Job " << cjob->name << ", so Job " << cjob->name << " paused and Job " << job->name << " started." << endl;
    join(cjob);
    cjob = job;
  } else join(job);
}

int main() {
  thread p(action);
  arrive(new Job("A", 5));
  this_thread::sleep_for(chrono::seconds(2)); // C++11д��
  arrive(new Job("B", 7));
  this_thread::sleep_for(2000ms);
  arrive(new Job("C", 3));
  this_thread::sleep_for(7000ms);
  arrive(new Job("D", 4));
  p.join();
  return 0;
}