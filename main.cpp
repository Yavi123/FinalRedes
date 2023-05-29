#include "src/include/SDL_Utils.h"
#include <iostream>
#include "src/include/InputManager.h"
#include "src/include/NetManager.h"
#include "src/include/StateMachine.h"
#include "src/include/StateMainMenu.h"

int main(int argc, char *argv[]) {
    
    SDL_Utils::Init();
    NetManager::Init(true, "aaaaa", "0.0.0.0", "7777");
    SDL_Utils* sdl = SDL_Utils::Instance();
    
    bool exit = false;

    InputManager* input = InputManager::Instance();

    StateMachine states = StateMachine();

    states.SetState<MainMenu>();

    while(!exit){
        
        input->UpdateEvents();
        exit = InputManager::Instance()->Quit();

        SDL_SetRenderDrawColor(sdl->Renderer(), 200, 200, 200, 200);
        SDL_RenderClear(sdl->Renderer());

        states.Update(0.01f);

        const char* error = SDL_GetError();
        if (error != "") {
            //std::cout << error << "\n";
            SDL_ClearError();
        }

        SDL_RenderPresent(sdl->Renderer());

    }

    InputManager::Clear();
    SDL_Utils::Clear();

    std::cout << "AAA\n";
    return 0;
}