#include <SDL.h>
#include <iostream>
#include "src/include/InputManager.h"

int main(int argc, char *argv[]){
    SDL_Window* window = NULL;

    if(SDL_Init(0)!=0){
        std::cout << "Error en la inicialización de SDL: " << SDL_GetError();
        return -1;
    }

    window = SDL_CreateWindow("Prueba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    if(window == NULL){
        std::cout << "Error en la creación de la ventana SDL: " << SDL_GetError();
        SDL_Quit();
        return -1;
    }

    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
    int x,y;
    SDL_GetWindowSize(window, &x, &y);
    SDL_Rect rect = {0, 0, x, y};
    SDL_FillRect(windowSurface, &rect, SDL_MapRGB(windowSurface->format, 255, 255, 255));
    SDL_UpdateWindowSurface(window);
    
    bool exit = false;

    InputManager* input = Input();

    while(!exit){
        
        input->UpdateEvents();

        exit = InputManager::Instance()->Quit();
        
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "AAA\n";
    return 0;
}