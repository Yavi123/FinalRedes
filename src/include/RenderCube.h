//Draw a rect cube
#ifndef RENDERCUBE_H
#define RENDERCUBE_H

#include "SDL_rect.h"
#include "Component.h"

class RenderCube: public Component
{
public:
    RenderCube();
    ~RenderCube();
    void update(float dt) override;
    void start() override;
    void awake(){};
    void setColor(const SDL_Color& c);

private:
    SDL_Rect rect;
    SDL_Color color;
};

#endif