//Executes PlayerController.h
#include "src/include/PlayerController.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"
#include "src/include/InputManager.h"
#include "src/include/NetManager.h"
#include "src/include/Redes/Message.h"
#include "src/include/Collider.h"


PlayerController::PlayerController() {
    speed = 150;
    shot = false;
}
PlayerController::~PlayerController() {

}
void PlayerController::start() {
    //std::cout << "PlayerController::start()\n";
}
void PlayerController::update(float dt) {
    //std::cout << "PlayerController::update()\n";
    if (!NetManager::Instance()->isTurn() || shot) {
        gameObject->getComponent<Transform>()->setVelocity({0, gameObject->getComponent<Transform>()->getVelocity().y});
        return;
    }
    bool input = false;
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_W)) {
        if(enSuelo){
            gameObject->getComponent<Transform>()->setVelocity({gameObject->getComponent<Transform>()->getVelocity().x, -speed*5});
        }
        input = true;
    }
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_S)) {
        if(enSuelo){
            gameObject->getComponent<Transform>()->setVelocity({gameObject->getComponent<Transform>()->getVelocity().x, +speed*5});
        }
        input = true;
    }
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
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_1)) {
		LoginMessage msg("Xx_MiNombre_xX");
		NetManager::Instance()->SendMessage(msg);
	}
}

void PlayerController::onCollisionExit(GameObject* other){
    //std::cout << "PlayerController::onCollisionExit()\n";
    if (gameObject->getComponent<Collider>()->IsTrigger() || other->getComponent<Collider>()->IsTrigger()) return;
    enSuelo = false;
}
bool PlayerController::isOnFloor(){
return enSuelo;
}
void PlayerController::setShot(bool b){
    shot = b;
}
