#include <map>

template<class T>
class DFA {
public:
    class State {
    public:
        void (*Enter)() = []{};
        void (*Leave)() = []{};
        // receive the signal will trigger current state to target state
        bool PointTo(T signal, State *target) {
            if (IsPointTo(signal)) return false;
            PointTowards.try_emplace(signal, target);
            return true;
        }
        // whether does the state have way to other state
        bool IsPointTo(T signal) { return PointTowards.find(signal) != PointTowards.end(); }
        // trigger the state leave function and target state enter function
        // return target state
        // if no way to point target state, there is no thing happen and return self
        State *Transfer(T signal) {
            if (!IsPointTo(signal)) return this;
            Leave();
            PointTowards[signal]->Enter();
            return PointTowards[signal];
        }
    private:
        // the state could go to which states
        // T is a signal to trigger the state to the target state
        std::map<T, State*> PointTowards;
    };

    DFA(State *start) : Current(start) {}

    // receive a signal to transfer current state
    bool Receive(T signal) {
        if (!Current->IsPointTo(signal)) return false;
        Current = Current->Transfer(signal);
        return true;
    }
private:
    State *Current;
};