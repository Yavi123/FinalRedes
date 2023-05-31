#include "src/include/StatePlaying.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"
#include "src/include/GravityComponent.h"
#include "src/include/RenderCube.h"
#include "src/include/PlayerController.h"
#include "src/include/Shooting.h"
#include <iostream>

Playing::Playing() : State() {

}
Playing::~Playing() {
    
}

void Playing::Init() {

    std::cout << toAdd.size() << "\n";

    GameObject* obj = new GameObject();
    obj->addComponent<PlayerController>();
    obj->addComponent<RenderCube>();
    obj->getComponent<RenderCube>()->start();
    obj->getComponent<RenderCube>()->setColor({255, 0, 0, 255});

    obj->addComponent<Shooting>();


    AddGameObject(obj);
}