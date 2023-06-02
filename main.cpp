#include "src/include/SDL_Utils.h"
#include <iostream>
#include "src/include/InputManager.h"
#include "src/include/NetManager.h"
#include "src/include/StateMachine.h"
#include "src/include/StateMainMenu.h"
#include "src/include/StatePlaying.h"
#include "src/include/CollissionManager.h"

int main(int argc, char *argv[]) {
    
    std::string s;
    std::string nick;
    std::cout << "host o cliente?:";
    std::cin >> s;
    if(s == "h" || s == "host"){
        std::cout << "Introduzca ip: ";
        std::cin >> s;
        std::cout << "Introduzca su nickname: ";
        std::cin >> nick;
        NetManager::Init(true, nick.c_str(), s.c_str(), "8080");
    }if(s == "c" || s == "cliente"){
        std::cout << "Introduzca su ip: ";
        std::cin >> s;
        std::cout << "Introduzca su nickname: ";
        std::cin >> nick;
        NetManager::Init(false, nick.c_str(), s.c_str(), "8080");
    }
    SDL_Utils::Init();
    CollissionManager::init();
    SDL_Utils* sdl = SDL_Utils::Instance();
    
    bool exit = false;

    InputManager* input = InputManager::Instance();

    StateMachine states = StateMachine();

    NetManager::Instance()->SetStateMachine(&states);

    states.SetState<MainMenu>();
    
    Uint32 last = SDL_GetTicks();

    while(!exit){
        
        Uint32 delta = SDL_GetTicks() - last;
        last = SDL_GetTicks();
        
        NetManager::Instance()->receive();
        NetManager::Instance()->process();

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