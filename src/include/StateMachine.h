#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "State.h"
#include <utility>
#include "CollissionManager.h"

class StateMachine
{
public:

    template <typename T, typename ...Targs>
    State* SetState(Targs &&...args) {
        if (current == nullptr) {
            current = new T();
            CollissionManager::getInstance()->reset();
            current->Init(std::forward(args)...);
            current->Start();
            return current;
        } else {
            toChangeTo = new T();
            CollissionManager::getInstance()->reset();
            toChangeTo->Init(std::forward(args)...);
            toChangeTo->Start();
            return toChangeTo;
        }
    };

    void LoadSavedState() {
        State* aux = current;
        current = saved;
        saved = aux;
    };

    template <typename T, typename ...Targs>
    void SaveStateAndSet(Targs &&...args) {
        LoadSavedState();
        SetState<T>(std::forward(args)...);
    };

    void Update(float dT);

private:
    State* current;
    State* saved;
    State* toChangeTo = nullptr;
};

#endif