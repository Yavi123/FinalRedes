#include "src/include/State.h"
#include "src/include/GameObject.h"
#include "src/include/CollissionManager.h"

State::State() {
    gameObjects = std::list<GameObject*>();
    colman = CollissionManager::getInstance();
}
State::~State() {}
GameObject* State::AddGameObject() {
    auto obj = new GameObject();
    gameObjects.push_back(obj);
    obj->context = this;
    return obj;
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
    colman->checkCollissions();
}