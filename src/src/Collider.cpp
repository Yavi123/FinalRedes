#include "src/include/Collider.h"
#include "src/include/GameObject.h"
#include "src/include/RenderCube.h"
#include "src/include/Transform.h"

Collider::Collider() : collider({0,0,1,1}), callBacks() {};

Collider::~Collider(){};

void Collider::initComponent(const SDL_Rect& coll){
    collider.w =coll.w;
    collider.h = coll.h;
    collider.x = coll.x;
    collider.y = coll.y;
}

void Collider::update(float dt){
    //TODO
    collider.x = gameObject->getTransform()->getPosition().x;
    collider.y = gameObject->getTransform()->getPosition().y;
}

void Collider::start(){
    RenderCube* render = gameObject->getComponent<RenderCube>();
    if(render!=nullptr){
        collider.h = render->getHeight();
        collider.w = render->getWidth();
    }
    collider.x = gameObject->getTransform()->getPosition().x;
    collider.y = gameObject->getTransform()->getPosition().y;
}
