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
#include "src/include/Redes/Message.h"
#include "src/include/StateMachine.h"
#include "src/include/StateMainMenu.h"
#include "src/include/NetManager.h"

Playing::Playing() : State() {

}
Playing::~Playing() {
    
}

void Playing::Init() {
    GameObject* obj = new GameObject();
    obj->getTransform()->setPosition(200 - 25, 400);
    obj->addComponent<PlayerController>();
    obj->addComponent<Shooting>();
    obj->addComponent<RenderCube>();
    obj->addComponent<Collider>();
    obj->addComponent<Health>();
    obj->addComponent<GravityComponent>();

    GameObject* obj2 = new GameObject();
    obj2->getTransform()->setPosition(600 - 25, 400);
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
    techo->getTransform()->setPosition(0, -90);
    techo->getTransform()->setSize(800, 100);
    techo->addComponent<RenderCube>();
    techo->getComponent<RenderCube>()->setColor({48, 20, 3, 255});
    techo->addComponent<Collider>();

    GameObject* plataforma = new GameObject();
    plataforma->getTransform()->setPosition(250, 400);
    plataforma->getTransform()->setSize(300, 15);
    plataforma->addComponent<RenderCube>();
    plataforma->getComponent<RenderCube>()->setColor({110, 100, 100, 255});
    plataforma->addComponent<Collider>();

    AddGameObject(obj);
    AddGameObject(obj2);
    AddGameObject(suelo);
    AddGameObject(paredIzq);
    AddGameObject(paredDer);
    AddGameObject(techo);
    AddGameObject(plataforma);
}

void Playing::HandleMessage(const Message& msg) {
    switch (msg.type){
        case POSITION: {
            PositionMessage pMsg;
            pMsg.from_bin(msg.data());
            GameObject* obj = GetGameObjectById(pMsg.gObjectId);
            obj->getTransform()->setPosition(pMsg.position);
        }
        break;
        case NEWOBJECT: {
            NewObjectMessage nMsg;
            nMsg.from_bin(msg.data());
            GameObject* obj = nMsg.result;
            AddGameObject(obj);
        }
        break;
        case DESTROYOBJECT: {
            DestroyObjectMessage dMsg;
            dMsg.from_bin(msg.data());
            GameObject* obj = GetGameObjectById(dMsg.idToKill);
            DestroyGameObject(obj);
        }
        break;
        case REDUCEHEALTH: {
            ReduceHealthMessage rMsg;
            rMsg.from_bin(msg.data());
            GameObject* obj = GetGameObjectById(rMsg.idToCheck);
            obj->getComponent<Health>()->SubstractHealth(rMsg.newHealth);
        }
        break;
        case LOGOUT:
            NetManager::Instance()->setAsHost();
            stMachine->SetState<MainMenu>(); 
            break;
        default:
            break;
    }
}