//Applies gravity to gameobjects that have this component
#ifndef _GRAVITY_H_
#define _GRAVITY_H_

#include "src/include/Component.h"

class GravityComponent : public Component
{
    public:
    __CMPID_DECL__(CMP_GRAVITY)
        GravityComponent();
        GravityComponent(float g);
        ~GravityComponent();
        void update(float dt) override;
        void start() override;
        void awake(){};
    private:
        float gravity;
        
};

#endif
