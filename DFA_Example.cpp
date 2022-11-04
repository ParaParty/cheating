#include "DFA.hpp"
#include <iostream>
using namespace std;

string NumberString = "";

int main() {
    map<char, bool> IsNum {
        {'0', true}, {'1', true}, {'2', true}, {'3', true}, {'4', true}, {'5', true}, {'6', true}, {'7', true}, {'8', true}, {'9', true},
        {'[', false}, {']', false}, {',', false}
    };
    // NUM状态为读入的字符为数码 SEQ状态为读入的字符为符号
    enum State { NUM, SEQ };
    // 以函数指针类型作为模版类参数 string&记录收集起来的数码 ch为当前需要收集的数码 vector<int>&为所有数收集后的结果集合
    DFA<void(*)(string&, char, vector<int>&)> dfa(SEQ);
    // 增加从NUM到NUM状态的转移 当发生此转移时 str收集ch数码
    dfa.AddPointer(NUM, NUM, [](string &str, char ch, vector<int> &nums) { str += ch; });
    // 增加从SEQ到NUM状态的转移 当发生此转移时 str清空并收集第一个ch数码
    dfa.AddPointer(SEQ, NUM, [](string &str, char ch, vector<int> &nums) { str = ch; });
    // 增加从NUM到SEQ状态的转移 当发生此转移时 将str转换成整型存入nums中
    dfa.AddPointer(NUM, SEQ, [](string &str, char ch, vector<int> &nums) { nums.push_back(stoi(str)); });
    // 增加从SEQ到SEQ状态的转移 当发生此转移时 将什么事都不做
    dfa.AddPointer(SEQ, SEQ, [](string &str, char ch, vector<int> &nums) {});
    // str为用于读入输入的字符串 temp用于保存收集起来的数码
    string str, temp = "";
    // nums为整型结果集合
    vector<int> nums;
    cin >> str;
    // 遍历输入的字符串
    for (auto iter = str.begin(); iter != str.end(); iter++) {
        // 当此字符为数码 则将状态转移为NUM 并触发状态转移func
        if (IsNum[*iter]) dfa.MoveTo(NUM)(temp, *iter, nums);
        // 当此字符为符号 则将状态转移为SEQ 并触发状态转移func
        else dfa.MoveTo(SEQ)(temp, *iter, nums);
    }
    // 遍历输出nums
    for (auto iter = nums.begin(); iter != nums.end(); iter++) { cout << *iter << " "; }
    return 0;
}