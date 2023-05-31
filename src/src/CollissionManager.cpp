#include "src/include/GameObject.h"
#include "src/include/Collider.h"
#include "src/include/CollissionManager.h"
#include <cassert>

CollissionManager* CollissionManager::instance = nullptr;
void CollissionManager::registerObject(GameObject* go){
    assert(go->getComponent<Collider>()!=nullptr);
    colliders.push_back(go);
}

void CollissionManager::deregisterObject(GameObject* go){
    for(auto it = colliders.begin(); it!= colliders.end();){
        if(*it==go){
            it = colliders.erase(it);
        }else{
            ++it;
        }
    }
}

void CollissionManager::checkCollissions(){
    for(int i = 0; i < colliders.size(); i++){
        Collider* coll = colliders[i]->getComponent<Collider>();
        for(int j = i+1; j < colliders.size(); j++){         
            if(coll->isColliding(colliders[j])){
                colliders[i]->onCollission(colliders[j]);
                colliders[j]->onCollission(colliders[i]);
            }
        }
    }
}

CollissionManager* CollissionManager::getInstance(){
    if(instance == nullptr)
        CollissionManager::init();
    return instance;
}

CollissionManager* CollissionManager::init(){
    assert(instance == nullptr);
    instance = new CollissionManager();
    return instance;
}

void CollissionManager::clear(){
    delete instance;
    instance = nullptr;
}

void CollissionManager::reset(){
    colliders.clear();
}