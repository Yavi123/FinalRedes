#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include <unordered_map>

class InputManager {
public:
    static void Init();
    static InputManager* Instance();
    static void Clear();

    void UpdateEvents();
    bool Quit();
    bool KeyPressed(SDL_Scancode key);
    bool MouseClick();
    const SDL_Point& MousePosition();

private:
    InputManager();
    ~InputManager() = default;
    static InputManager* _instance;
    bool _quit;
    bool _mouseDown;
    SDL_Point _mousePosition;
    std::unordered_map<SDL_Scancode, bool> _inputs;

};

extern InputManager* Input();

#endif