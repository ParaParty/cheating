#include "DFA.hpp"
#include <iostream>
using namespace std;

string NumberString = "";

int main() {
    map<char, bool> IsNum {
        {'0', true}, {'1', true}, {'2', true}, {'3', true}, {'4', true}, {'5', true}, {'6', true}, {'7', true}, {'8', true}, {'9', true},
        {'[', false}, {']', false}, {',', false}
    };
    enum State { NUM, SEQ };
    DFA<void(*)(string&, char, vector<int>&)> dfa(SEQ);
    dfa.AddPointer(NUM, NUM, [](string &str, char ch, vector<int> &nums) { str += ch; });
    dfa.AddPointer(SEQ, NUM, [](string &str, char ch, vector<int> &nums) { str = ch; });
    dfa.AddPointer(NUM, SEQ, [](string &str, char ch, vector<int> &nums) { nums.push_back(stoi(str)); });
    dfa.AddPointer(SEQ, SEQ, [](string &str, char ch, vector<int> &nums) {});
    string str, temp = "";
    vector<int> nums;
    cin >> str;
    for (auto iter = str.begin(); iter != str.end(); iter++) {
        if (IsNum[*iter]) dfa.MoveTo(NUM)(temp, *iter, nums);
        else dfa.MoveTo(SEQ)(temp, *iter, nums);
    }
    for (auto iter = nums.begin(); iter != nums.end(); iter++) { cout << *iter << " "; }
    return 0;
}