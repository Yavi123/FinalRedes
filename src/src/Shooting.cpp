#include "src/include/Shooting.h"
#include "src/include/GameObject.h"
#include "src/include/RenderCube.h"
#include "src/include/Transform.h"
#include "src/include/InputManager.h"
#include "src/include/GravityComponent.h"
#include "src/include/State.h"
#include "src/include/Bullet.h"
#include "src/include/Health.h"
#include "src/include/Collider.h"
#include "src/include/Redes/Message.h"
#include "src/include/NetManager.h"
#include "src/include/PlayerController.h"

Shooting::Shooting() {};

Shooting::~Shooting(){};

void Shooting::update(float dt){
    if(!NetManager::Instance()->isTurn()) return;
    if (Input()->MouseClick()) {
        auto bala = new GameObject();
        bala->getTransform()->setPosition(
            gameObject->getTransform()->getPosition() + 
            Vector2({gameObject->getTransform()->getSize().x / 2.f - 7, gameObject->getTransform()->getSize().y / 2.f - 15})
            );
        bala->getTransform()->setSize({14, 30});
        bala->addComponent<GravityComponent>();
        bala->addComponent<Bullet>();
        bala->getComponent<Bullet>()->SetIgnore(gameObject->getComponent<Health>());
        bala->addComponent<RenderCube>();
        Vector2 dir = {
            (float)Input()->MousePosition().x - bala->getTransform()->getPosition().x, 
            (float)Input()->MousePosition().y - bala->getTransform()->getPosition().y
            };
        bala->getTransform()->setVelocity(dir.x * 3, dir.y * 3);
        bala->addComponent<Collider>();
        bala->getComponent<Collider>()->SetAsTrigger();

        gameObject->context->AddGameObject(bala);
        bala->getComponent<RenderCube>()->setColor({0, 0, 255, 255});

        if(gameObject->getComponent<PlayerController>() != nullptr){
            gameObject->getComponent<PlayerController>()->setShot(true);
        }

        NewObjectMessage msg(bala);
        NetManager::Instance()->SendMessage(msg);
        NetManager::Instance()->changeTurn();
    }
}

void Shooting::start(){
    
}
