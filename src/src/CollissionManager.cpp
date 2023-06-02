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
                if(!wasColliding(i, j)){
                    setWasColliding(i, j, true);
                }
            }
            else{
                if(wasColliding(i, j)){
                    setWasColliding(i, j, false);
                    colliders[i]->onCollisionExit(colliders[j]);
                    colliders[j]->onCollisionExit(colliders[i]);
                }
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

bool CollissionManager::wasColliding(int i, int j){
    for(Collission c : collissions){
        if((c.i == i && c.j == j)){
            return true;
        }
    }
    return false;
}
void CollissionManager::setWasColliding(int i, int j, bool value){
    Collission c;
    c.i = i;
    c.j = j;
    if(value){
        collissions.push_back(c);
    }
    else{
        for(auto it = collissions.begin(); it != collissions.end();){
            if(it->i == i && it->j == j){
                it = collissions.erase(it);
            }else{
                ++it;
            }
        }
    }
}