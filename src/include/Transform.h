//Transform component
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "Component.h"
#include "ECSDefs.h"
#include "Vector2.h"
#include <SDL.h>

class Transform : public Component
{
    public:
    __CMPID_DECL__(CMP_TRANSFORM)
        Transform();
        Transform(float x, float y);
        ~Transform();
        void update(float dt) override;
        void start() override;
        void awake(){};

        void setPosition(const Vector2& pos);
        void setPosition(float x, float y);
        Vector2 getPosition();

        void setVelocity(const Vector2& v);
        void setVelocity(float x, float y);
        Vector2 getVelocity();

        void translate(float x, float y);
    private:
        Vector2 position;
        Vector2 velocity;  
        
};

#endif