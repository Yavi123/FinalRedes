#include "src/include/InputManager.h"
#include <SDL_events.h>

InputManager* InputManager::_instance = nullptr;

InputManager::InputManager() {
    _quit = false;
    _inputs = std::unordered_map<SDL_Scancode, bool>();
}

void InputManager::Init() {
    if (!_instance)
        _instance = new InputManager();
}

InputManager* InputManager::Instance() {
    if (!_instance)
        InputManager::Init();
    return _instance;
}

void InputManager::Clear() {
    if (_instance) {
        delete _instance;
        _instance = nullptr;
    }
}

void InputManager::UpdateEvents() {

    _quit = false;
    _inputs.clear();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type){
                case SDL_QUIT:
                    _quit=true;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        _quit = true;
                    }
                    else {
                        _inputs.insert(std::pair<SDL_Scancode, bool>(event.key.keysym.scancode, true));
                    }
                    break;
                default:
                    break;
            }
    }
}

bool InputManager::Quit() {
    return _quit;
}

bool InputManager::KeyPressed(SDL_Scancode key) {
    return _inputs[key];
}