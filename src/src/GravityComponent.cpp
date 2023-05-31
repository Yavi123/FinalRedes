//Executes GravityComponent.h

#include "src/include/GravityComponent.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"
#include <iostream>

GravityComponent::GravityComponent() {
    gravity = .0098f;
}
GravityComponent::GravityComponent(float g) {
    gravity = g;
}

GravityComponent::~GravityComponent() {

}
void GravityComponent::start() {

}

void GravityComponent::update(float dt) {
    //std::cout << "GravityComponent::update()\n";  
    float x = gameObject->getComponent<Transform>()->getVelocityX();
    float y = gameObject->getComponent<Transform>()->getVelocityY();
    y = y + gravity * dt;
    gameObject->getComponent<Transform>()->setVelocity(x, y);
}