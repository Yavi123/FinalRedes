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

        SDL_SetRenderDrawColor(SDL_Utils::Instance()->Renderer(), 200, 200, 200, 200);
        SDL_RenderClear(SDL_Utils::Instance()->Renderer());

        states.Update(0.01f);

        SDL_RenderPresent(SDL_Utils::Instance()->Renderer());

    }

    SDL_Utils::Clear();

    std::cout << "AAA\n";
    return 0;
}