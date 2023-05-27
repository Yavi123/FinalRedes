#include "src/include/StateMachine.h"
#include "src/include/SDL_Utils.h"

void StateMachine::Update(float dT) {
    if (current) {
        current->Update(dT);
        current->Render();
    }
}