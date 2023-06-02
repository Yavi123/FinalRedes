#ifndef MAINMENU_H
#define MAINMENU_H
#include "State.h"
#include "SDL_rect.h"
#include <string>

class Texture;
class SDL_Utils;

class MainMenu : public State
{
public:
    MainMenu();
    ~MainMenu();

    void Init() override;

    void HandleMessage(const Message& msg) override;

private:

    std::string opponent;
};

#endif