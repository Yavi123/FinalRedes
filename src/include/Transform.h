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
        float getVelocityX();
        float getVelocityY();
        void setVelocity(SDL_Point v);
        void setVelocity(float x, float y);
        void translate(float x, float y);
    private:
        SDL_Point position;
        float velocityX;       
        float velocityY;       
        
};

#endif