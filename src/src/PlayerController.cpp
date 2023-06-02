//Executes PlayerController.h
#include "src/include/PlayerController.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"
#include "src/include/InputManager.h"
#include "src/include/Collider.h"


PlayerController::PlayerController() {
    speed = 150;
}
PlayerController::~PlayerController() {

}
void PlayerController::start() {
    //std::cout << "PlayerController::start()\n";
}
void PlayerController::update(float dt) {
    //std::cout << "PlayerController::update()\n";
    bool input = false;
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_W)) {
        if(enSuelo){
            gameObject->getComponent<Transform>()->setVelocity({gameObject->getComponent<Transform>()->getVelocity().x, -speed*5});
        }
    }
    // if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_S)) {
    //     gameObject->getComponent<Transform>()->setVelocity({gameObject->getComponent<Transform>()->getVelocity().x, speed});
    //     input = true;
    // }
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_A)) {
        gameObject->getComponent<Transform>()->setVelocity({-speed, gameObject->getComponent<Transform>()->getVelocity().y});
        input = true;
    }
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_D)) {
        gameObject->getComponent<Transform>()->setVelocity({speed, gameObject->getComponent<Transform>()->getVelocity().y});
        input = true;
    }
    if (!input) {
        gameObject->getComponent<Transform>()->setVelocity({0, gameObject->getComponent<Transform>()->getVelocity().y});
    }
}

void PlayerController::onCollission(GameObject* other){
    //std::cout << "PlayerController::onCollission()\n";   
    if (gameObject->getComponent<Collider>()->IsTrigger() || other->getComponent<Collider>()->IsTrigger()) return;
    enSuelo = true;
}

void PlayerController::onCollisionExit(GameObject* other){
    //std::cout << "PlayerController::onCollisionExit()\n";
    if (gameObject->getComponent<Collider>()->IsTrigger() || other->getComponent<Collider>()->IsTrigger()) return;
    enSuelo = false;
}
 bool PlayerController::isOnFloor(){
    return enSuelo;
 }