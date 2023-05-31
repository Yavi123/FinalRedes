#include "src/include/State.h"
#include "src/include/GameObject.h"

State::State() {
    gameObjects = std::list<GameObject*>();
    toAdd = std::list<GameObject*>();
}
State::~State() {

}
void State::AddGameObject(GameObject* obj) {
    toAdd.push_back(obj);
    obj->context = this;
}
void State::Start() {
    for (GameObject* obj : gameObjects) {
        obj->start();
    }
}
void State::Update(float deltaTime) {
    for (GameObject* obj : toAdd) {
        gameObjects.push_back(obj);
    }
    toAdd.clear();
    for (GameObject* obj : gameObjects) {
        obj->update(deltaTime);
    }
}