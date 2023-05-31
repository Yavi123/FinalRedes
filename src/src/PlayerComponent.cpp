//Executes PlayerController.h
#include "src/include/PlayerController.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"
#include "src/include/InputManager.h"

PlayerController::PlayerController() {
    speed = 0;
}
void PlayerController::start() {
    //std::cout << "PlayerController::start()\n";
}
void PlayerController::update(float dt) {
    //std::cout << "PlayerController::update()\n";
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_W)) {
        gameObject->getComponent<Transform>()->translate(0, -speed * dt);
    }
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_S)) {
        gameObject->getComponent<Transform>()->translate(0, speed * dt);
    }
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_A)) {
        gameObject->getComponent<Transform>()->translate(-speed * dt, 0);
    }
    if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_D)) {
        gameObject->getComponent<Transform>()->translate(speed * dt, 0);
    }
}