#include "src/include/SDL_Utils.h"
#include <iostream>
#include "src/include/InputManager.h"
#include "src/include/StateMachine.h"
#include "src/include/StateMainMenu.h"

int main(int argc, char *argv[]) {
    
    SDL_Utils::Init();
    
    bool exit = false;

    InputManager* input = InputManager::Instance();

    StateMachine states = StateMachine();

    states.SetState<MainMenu>();

    while(!exit){
        
        input->UpdateEvents();
        exit = InputManager::Instance()->Quit();

        states.Update(0.01f);
    }

    SDL_Utils::Clear();

    std::cout << "AAA\n";
    return 0;
}