#include "DFA.hpp"
#include <iostream>
using namespace std;

int main() {
    DFA<char>::State a, b, c, d, start;
    start.PointTo('a' , &a);
    start.PointTo('b' , &b);
    start.PointTo('c' , &c);
    start.PointTo('d' , &d);
    a.PointTo('b', &b);
    b.PointTo('c', &c);
    c.PointTo('d', &d);
    d.PointTo('a', &a);
    start.Leave = [] { cout << "leave start "; };
    a.Enter = [] { cout << "to a" << endl; };
    a.Leave = [] { cout << "leave a "; };
    b.Enter = [] { cout << "to b" << endl; };
    b.Leave = [] { cout << "leave b "; };
    c.Enter = [] { cout << "to c" << endl; };
    c.Leave = [] { cout << "leave c "; };
    d.Enter = [] { cout << "to d " << endl; };
    d.Leave = [] { cout << "leave d "; };
    DFA<char> dfa(&start);
    string str;
    cin >> str;
    for (auto iter = str.begin(); iter != str.end(); iter++) {
        if (!dfa.Receive(*iter)) cout << "Error: Fail to transfer to " << *iter << endl;
    }
    return 0;
}