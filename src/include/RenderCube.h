//Draw a rect cube
#ifndef RENDERCUBE_H
#define RENDERCUBE_H

#include "SDL_Utils.h"
#include "Component.h"

class Transform;

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
private:
    SDL_Color color;
    Texture* _cube;
    Transform* tr;
};

#endif