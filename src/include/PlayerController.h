//Component that controls the player
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Component.h"

class PlayerController: public Component
{
    public:
    __CMPID_DECL__(CMP_PLAYERCONTROLLER)
        PlayerController();
        ~PlayerController();
        void update(float dt) override;
        void start() override;
        void awake(){};
        void onCollission(GameObject* other) override;
    private:
        float speed;
        bool enSuelo;
        
};

#endif
