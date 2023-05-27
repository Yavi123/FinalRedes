#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL_scancode.h>
#include <unordered_map>

class InputManager {
public:
    static void Init();
    static InputManager* Instance();
    static void Clear();

    void UpdateEvents();
    bool Quit();
    bool KeyPressed(SDL_Scancode key);

private:
    InputManager();
    ~InputManager() = default;
    static InputManager* _instance;
    bool _quit;
    std::unordered_map<SDL_Scancode, bool> _inputs;

};

InputManager* Input() {
    return InputManager::Instance();
}

#endif