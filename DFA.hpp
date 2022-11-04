#include <map>
#include <vector>
#define STATE std::size_t

template<class F>
class DFA {
public:
    // 当前状态
    STATE Current;
    // 基于初始状态构造DFA
    DFA(STATE start) : Current(start) {}
    // 增加从origin状态指向target状态的转移路径 定义转移时将会返回的func
    void AddPointer(STATE origin, STATE target, F func) { TransferActions[origin][target] = func; }
    // 将当前状态转移为目标状态 返回func
    F MoveTo(STATE target) {
        auto func = TransferActions[Current][target];
        Current = target;
        return func;
    }
private:
    // 转移func映射
    std::map<STATE, std::map<STATE, F>> TransferActions;
};