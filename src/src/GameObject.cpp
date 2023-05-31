#include "src/include/GameObject.h"
#include "src/include/Transform.h"

GameObject::GameObject() : currComponents(), _components() {
    transform = addComponent<Transform>();
    context = nullptr;
}
GameObject::~GameObject(){
    for(auto it = currComponents.begin(); it != currComponents.end(); it = currComponents.erase(it)){
        delete *it;
    }
  
}


void GameObject::update(float dt){
    for(Component* c : currComponents){
        c->update(dt);
    }
}
void GameObject::start(){
    for(Component* c: currComponents){
        c->start();
    }
}

void GameObject::onCollission(GameObject* other){
    for(Component* c: currComponents){
        c->onCollission(other);
    }
}