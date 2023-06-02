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
#include "src/include/Health.h"

Playing::Playing() : State() {

}
Playing::~Playing() {
    
}

void Playing::Init() {
    GameObject* obj = new GameObject();
    obj->getTransform()->setPosition(200, 400);
    obj->addComponent<PlayerController>();
    obj->addComponent<Shooting>();
    obj->addComponent<RenderCube>();
    obj->addComponent<Collider>();
    obj->addComponent<Health>();
    obj->addComponent<GravityComponent>();

    GameObject* obj2 = new GameObject();
    obj2->getTransform()->setPosition(600, 400);
    obj2->addComponent<RenderCube>();
    obj2->addComponent<Collider>();
    obj2->addComponent<Health>();
    obj2->addComponent<GravityComponent>();

    GameObject* suelo = new GameObject();
    suelo->getTransform()->setPosition(0, 550);
    suelo->getTransform()->setSize(800, 50);
    suelo->addComponent<RenderCube>();
    suelo->getComponent<RenderCube>()->setColor({48, 20, 3, 255});
    suelo->addComponent<Collider>();

    GameObject* paredIzq = new GameObject();
    paredIzq->getTransform()->setPosition(0, 0);
    paredIzq->getTransform()->setSize(70, 550);
    paredIzq->addComponent<RenderCube>();
    paredIzq->getComponent<RenderCube>()->setColor({48, 20, 3, 255});
    paredIzq->addComponent<Collider>();

    GameObject* paredDer = new GameObject();
    paredDer->getTransform()->setPosition(730, 0);
    paredDer->getTransform()->setSize(70, 550);
    paredDer->addComponent<RenderCube>();
    paredDer->getComponent<RenderCube>()->setColor({48, 20, 3, 255});
    paredDer->addComponent<Collider>();

    GameObject* techo = new GameObject();
    techo->getTransform()->setPosition(0, 0);
    techo->getTransform()->setSize(800, 10);
    techo->addComponent<RenderCube>();
    techo->getComponent<RenderCube>()->setColor({48, 20, 3, 255});
    techo->addComponent<Collider>();



    //obj->addComponent<Shooting>();

    AddGameObject(obj);
    AddGameObject(obj2);
    AddGameObject(suelo);
    AddGameObject(paredIzq);
    AddGameObject(paredDer);
    AddGameObject(techo);
}