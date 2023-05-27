#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "State.h"

class StateMachine
{
public:

    template <typename T, typename ...Targs>
    void SetState(Targs &&...args) {
        if (current != nullptr)
            delete current;
        current = new T();
        current.Init(std::forward(args));
        return current;
    }

    void LoadSavedState() {
        State* aux = current;
        current = saved;
        saved = aux;
    }

    template <typename T, typename ...Targs>
    void SaveStateAndSet(Targs &&...args) {
        LoadSavedState()
        SetState<T>(std::forward(args));
    }

    void Update(float dT) {
        if (current) {
            current->Update(dT);
            current->Render();
        }
    }

private:
    State* current;
    State* saved;
};

#endif