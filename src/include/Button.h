#ifndef BUTTON_H
#define BUTTON_H

#include "SDL_Utils.h"
#include "Component.h"
#include <functional>

class Transform;

class Button: public Component
{
public:
    __CMPID_DECL__(CMP_BUTTON)
    Button();
    ~Button();
    void update(float dt) override;
    void start() override;
    void awake(){};
    void SetOnClick(const std::function<void()>& onClick);
private:
    std::function<void()> onClick;
};

#endif