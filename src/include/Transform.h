//Transform component
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "Component.h"
#include "ECSDefs.h"
#include <SDL.h>

class Transform : public Component
{
    public:
    __CMPID_DECL__(CMP_TRANSFORM)
        Transform();
        Transform(int x, int y);
        ~Transform();
        void update(float dt) override;
        void start() override;
        void awake(){};
        void setX(int x);
        void setY(int y);
        SDL_Point getPosition();
        SDL_Point getVelocity();
        void setVelocity(SDL_Point v);
        void setVelocity(int x, int y);
    private:
        SDL_Point position;
        SDL_Point velocity;       
        
};

#endif