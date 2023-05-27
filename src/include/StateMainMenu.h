#ifndef MAINMENU_H
#define MAINMENU_H
#include "State.h"
#include "SDL_rect.h"

class Texture;
class SDL_Utils;

class MainMenu : public State
{
public:
    MainMenu();
    ~MainMenu();

    void Init() override;

    void Update(float deltaTime) override;
    void Render() override;

private:
    SDL_Utils* sdl;
    Texture* img;

    SDL_Rect dest;
};

#endif