#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "ECSDefs.h"

class GameObject;
class Component
{
    public:
        Component() = default;
        virtual ~Component() = default;
        inline void setContext(GameObject* go) {gameObject = go;};
        void initComponent() {};
        virtual void awake(){};
        virtual void update(float dt){};
        virtual void start(){};
        virtual void onCollission(GameObject* other) {};

    protected:
        GameObject* gameObject;   
};
#endif