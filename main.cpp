#include "src/include/SDL_Utils.h"
#include <iostream>
#include "src/include/InputManager.h"
#include "src/include/NetManager.h"
#include "src/include/StateMachine.h"
#include "src/include/StateMainMenu.h"
#include "src/include/StatePlaying.h"

int main(int argc, char *argv[]) {
    
    SDL_Utils::Init();
    NetManager::Init(true, "aaaaa", "0.0.0.0", "7777");
    SDL_Utils* sdl = SDL_Utils::Instance();
    
    bool exit = false;

    InputManager* input = InputManager::Instance();

    StateMachine states = StateMachine();

    states.SetState<Playing>();
    
    Uint32 last = SDL_GetTicks();

    while(!exit){
        
        Uint32 delta = SDL_GetTicks() - last;
        last = SDL_GetTicks();

        input->UpdateEvents();
        exit = InputManager::Instance()->Quit();

        SDL_SetRenderDrawColor(sdl->Renderer(), 200, 200, 200, 200);
        SDL_RenderClear(sdl->Renderer());

        states.Update(delta / 1000.f);

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