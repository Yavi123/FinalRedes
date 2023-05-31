#include "src/include/StatePlaying.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"
#include "src/include/GravityComponent.h"
#include "src/include/RenderCube.h"
#include "src/include/PlayerController.h"
#include "src/include/Shooting.h"
#include "src/include/CollissionManager.h"
#include <iostream>
#include "src/include/Collider.h"

Playing::Playing() : State() {

}
Playing::~Playing() {
    
}

void Playing::Init() {
    GameObject* obj = new GameObject();
    obj->addComponent<PlayerController>();
    obj->addComponent<RenderCube>();
    obj->getComponent<RenderCube>()->start();
    obj->getComponent<RenderCube>()->setColor({255, 0, 0, 255});
    obj->addComponent<Collider>();

    GameObject* obj2 = new GameObject();
    obj2->getTransform()->setPosition(10,100);
    obj2->addComponent<RenderCube>();
    obj2->getComponent<RenderCube>()->setColor({255, 0, 0, 255});
    obj2->addComponent<Collider>();

    //obj->addComponent<Shooting>();

    AddGameObject(obj);
    AddGameObject(obj2);
}