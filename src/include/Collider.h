#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include "Component.h"
#include "ECSDefs.h"
#include <vector>
#include <SDL_rect.h>

class Collider;

typedef void (*OnColissionCallback)(Collider* other);

class Collider:public Component
{
    public:
        __CMPID_DECL__(CMP_COLLIDER)
        Collider();
        ~Collider();
        virtual void awake() {};
        inline void initComponent(){};
        void initComponent(const SDL_Rect& coll);
        void start() override;
        void update(float dt) override;

        
    protected:
        std::vector<OnColissionCallback> callBacks;
        SDL_Rect collider;
};

#endif