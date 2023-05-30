#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "src/include/ECSDefs.h"

class GameObject;
class Component
{
    public:
        Component();
        virtual ~Component();
        void setContext(GameObject* go);
        void awake(){};
        virtual void update(float dt) = 0;
        virtual void start() = 0;

    protected:
        GameObject* gameObject;   
};
#endif