#include "src/include/Shooting.h"
#include "src/include/GameObject.h"
#include "src/include/RenderCube.h"
#include "src/include/Transform.h"
#include "src/include/InputManager.h"
#include "src/include/GravityComponent.h"
#include "src/include/State.h"

Shooting::Shooting() {};

Shooting::~Shooting(){};

void Shooting::update(float dt){
    if (Input()->MouseClick()) {
        std::cout << dt << "\n";
        auto bala = gameObject->context->AddGameObject();
        bala->getTransform()->setPosition(gameObject->getTransform()->getPosition());
        bala->addComponent<GravityComponent>();
        bala->addComponent<RenderCube>();
        bala->getComponent<RenderCube>()->setColor({0, 0, 255, 255});
        Vector2 dir = {
            bala->getTransform()->getPosition().x - Input()->MousePosition().x, 
            bala->getTransform()->getPosition().y - Input()->MousePosition().y
            };
        bala->getTransform()->setVelocity(dir.x / 100, dir.y / 100);
    }
}

void Shooting::start(){
    
}
