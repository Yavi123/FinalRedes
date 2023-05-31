#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include "Component.h"
#include "ECSDefs.h"
#include <vector>
#include <SDL_rect.h>

class Vector2;

typedef void (*OnColissionCallback)(GameObject* other);

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
        bool isColliding(GameObject* other);
        
    protected:
        // checks if two boxes o1 and o2 collides
	    bool collides( //
			const Vector2 &o1Pos, float o1Width, float o1Height, //
			const Vector2 &o2Pos, float o2Width, float o2Height);

	    // checks if two boxed o1 and o2 collides, taking into account the rotation of both
	    bool collidesWithRotation( //
			const Vector2 &o1Pos, float o1Width, float o1Height, float o1Rot, //
			const Vector2 &o2Pos, float o2Width, float o2Height, float o2Rot);

        bool PointInTriangle(const Vector2 &A, const Vector2 &B,
			const Vector2 &C, const Vector2 &P);

        // checks if the point P is in the rectangle defined by the rectangle
        //
        //     A --- B
        //     |     |
        //     |     |
        //     D --- C
        //
	    bool PointInRectangle(const Vector2 &A, const Vector2 &B,
			const Vector2 &C, const Vector2 &D, const Vector2 &P);

        SDL_Rect collider;
};

#endif