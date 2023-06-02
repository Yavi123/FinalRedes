#include "src/include/State.h"
#include "src/include/GameObject.h"
#include "src/include/CollissionManager.h"

State::State() {
    gameObjects = std::list<GameObject*>();
    colman = CollissionManager::getInstance();
    toAdd = std::list<GameObject*>();
}
State::~State() {}

void State::AddGameObject(GameObject* obj) {
    toAdd.push_back(obj);
    obj->context = this;
}
void State::DestroyGameObject(GameObject* obj) {
    if (toDelete.back() != obj)
    toDelete.push_back(obj);
}
void State::Start() {
    for (GameObject* obj : gameObjects) {
        obj->start();
    }
}
void State::Update(float deltaTime) {
    for (GameObject* obj : toAdd) {
        gameObjects.push_back(obj);
        obj->start();
    }
    toAdd.clear();
    for (GameObject* obj : gameObjects) {
        obj->update(deltaTime);
    }
    colman->checkCollissions();
    for (GameObject* obj : toDelete) {
        gameObjects.remove(obj);
        delete obj;
    }
    toDelete.clear();
}

GameObject* State::GetGameObjectById(uint16_t id){
    for(GameObject* obj : gameObjects){
        if(obj->id == id){
            return obj;
        }
    }
    return nullptr;
}