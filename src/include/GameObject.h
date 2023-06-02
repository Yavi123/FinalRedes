
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "src/include/ECSDefs.h"
#include "src/include/Component.h"
#include <list>
#include <cassert>
#include <iostream>
#include <array>

class Transform;
class State;

class GameObject{
    public:
        GameObject();
        ~GameObject();

        void update(float dt);
        void start();
        void onCollission(GameObject* other);
        void onCollisionExit(GameObject* other);

        template <typename T, typename ...Ts>
        inline T* addComponent(Ts ...args){

            constexpr cmpId_type cId = T::id;
            assert(cId < maxComponentId);

            // delete the current component, if any
            //
            removeComponent<T>();

            // create, initialise and install the new component
            //
            auto c = new T();
            c->setContext(this);
            c->initComponent(std::forward<Ts>(args)...);
            c->awake();
            _components[cId] = c;
            currComponents.push_back(c);

            // return it to the user so i can be initialised if needed
            return c;
        }

        template <typename T>
        void removeComponent(){
            constexpr cmpId_type cId = T::id;
            assert(cId < maxComponentId);

            if (_components[cId] != nullptr) {

                currComponents.remove(_components[cId]);
                // destroy it
                //
                delete _components[cId];

                // remove the pointer
                //
                _components[cId] = nullptr;
            }
        }

        template <typename T>
        inline T* getComponent(){
            constexpr cmpId_type cId = T::id;
		    assert(cId < maxComponentId);
		    return static_cast<T*>(_components[cId]);
        }

        inline Transform* getTransform(){return transform;};

        void SetContext(State* state) {context = state;};
    
        u_int16_t id;
        
        State* context;
    protected:
        std::array<Component*, maxComponentId> _components;
        std::list<Component*> currComponents; 
        Transform* transform;

        static u_int16_t numOfGameObjects;
};
#endif