#include "src/include/StateMachine.h"
#include "src/include/SDL_Utils.h"
#include <iostream>

void StateMachine::Update(float dT) {
    if (current) {
        current->Update(dT);
    }
    if (toChangeTo != nullptr) {
        delete current;
        current = toChangeTo;
        toChangeTo = nullptr;
    }
}