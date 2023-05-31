//Draw a rect cube
#ifndef RENDERCUBE_H
#define RENDERCUBE_H

#include "SDL_rect.h"
#include "Component.h"

class RenderCube: public Component
{
public:
    __CMPID_DECL__(CMP_RENDERCUBE)
    RenderCube();
    ~RenderCube();
    void update(float dt) override;
    void start() override;
    void awake(){};
    void setColor(const SDL_Color& c);
    inline int getWidth() {return rect.w;};
    inline int getHeight() {return rect.h;};
private:
    SDL_Rect rect;
    SDL_Color color;
};

#endif