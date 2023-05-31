//Executes PlayerController.h
#include "src/include/PlayerController.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"
#include "src/include/InputManager.h"


PlayerController::PlayerController() {
    speed = 5;
}
PlayerController::~PlayerController() {

}
void PlayerController::start() {
    //std::cout << "PlayerController::start()\n";
}
void PlayerController::update(float dt) {
    //std::cout << "PlayerController::update()\n";
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_W)) {
        gameObject->getComponent<Transform>()->translate(0, -speed);
    }
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_S)) {
        gameObject->getComponent<Transform>()->translate(0, speed);
    }
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_A)) {
        gameObject->getComponent<Transform>()->translate(-speed, 0);
    }
    // if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_D)) {
    //     gameObject->getComponent<Transform>()->translate(speed, 0);
    // }
}