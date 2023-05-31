#include "src/include/InputManager.h"
#include <SDL_events.h>
#include <iostream>

InputManager* InputManager::_instance = nullptr;

InputManager::InputManager() {
    _quit = false;
    _mouseDown = false;
    _mousePosition = {0, 0};
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
    _mouseDown = false;

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
                        std::cout << "Down\n";
                        if (_inputs.find(event.key.keysym.scancode) != _inputs.end())
                            _inputs.at(event.key.keysym.scancode) = true;
                        else
                            _inputs.emplace(event.key.keysym.scancode, true);
                    }
                    break;
                case SDL_KEYUP:
                    if (event.key.keysym.scancode != SDL_SCANCODE_ESCAPE) {
                        std::cout << "Up\n";
                        if (_inputs.find(event.key.keysym.scancode) != _inputs.end())
                            _inputs.at(event.key.keysym.scancode) = false;
                        else
                            _inputs.emplace(event.key.keysym.scancode, false);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    _mouseDown = true;
                    break;
                case SDL_MOUSEMOTION:
                    _mousePosition = {event.motion.x, event.motion.y};
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

bool InputManager::MouseClick() {
    return _mouseDown;
}
const SDL_Point& InputManager::MousePosition() {
    return _mousePosition;
}

InputManager* Input(){
    return InputManager::Instance();
}