#include <map>
#include <vector>
#define STATE std::size_t

template<class T>
class DFA {
public:
    STATE Current;
    DFA(STATE start) : Current(start) {}
    void AddPointer(STATE origin, STATE target, T func) { TransferActions[origin][target] = func; }
    T MoveTo(STATE target) {
        auto func = TransferActions[Current][target];
        Current = target;
        return func;
    }
private:
    std::map<STATE, std::map<STATE, T>> TransferActions;
};