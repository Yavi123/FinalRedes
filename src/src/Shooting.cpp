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

Shooting::Shooting() {};

Shooting::~Shooting(){};

void Shooting::update(float dt){
    if (Input()->MouseClick()) {
        std::cout << dt << "\n";
        auto bala = new GameObject();
        bala->getTransform()->setPosition(gameObject->getTransform()->getPosition());
        bala->addComponent<GravityComponent>();
        bala->addComponent<Bullet>();
        bala->getComponent<Bullet>()->SetIgnore(gameObject->getComponent<Health>());
        bala->addComponent<RenderCube>();
        bala->getComponent<RenderCube>()->start();
        bala->getComponent<RenderCube>()->setColor({0, 0, 255, 255});
        Vector2 dir = {
            (float)Input()->MousePosition().x - bala->getTransform()->getPosition().x, 
            (float)Input()->MousePosition().y - bala->getTransform()->getPosition().y
            };
        bala->getTransform()->setVelocity(dir.x * 3, dir.y * 3);
        bala->addComponent<Collider>();

        gameObject->context->AddGameObject(bala);

    }
}

void Shooting::start(){
    
}
