#include "src/include/State.h"
#include "src/include/GameObject.h"

State::State() {
    gameObjects = std::list<GameObject*>();
}
State::~State() {

}
void State::Start() {
    for (GameObject* obj : gameObjects) {
        obj->start();
    }
}
void State::Update(float deltaTime) {
    for (GameObject* obj : gameObjects) {
        obj->update(deltaTime);
    }
}