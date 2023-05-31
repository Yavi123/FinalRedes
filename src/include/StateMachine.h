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
        if (current != nullptr)
            delete current;
        CollissionManager::getInstance()->reset();
        current = new T();
        current->Init(std::forward(args)...);
        current->Start();
        return current;
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
};

#endif