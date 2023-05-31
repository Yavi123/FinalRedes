//Executes GravityComponent.h

#include "src/include/GravityComponent.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"
#include <iostream>

GravityComponent::GravityComponent() {
    gravity = 980.f;
}
GravityComponent::GravityComponent(float g) {
    gravity = g;
}

GravityComponent::~GravityComponent() {

}
void GravityComponent::start() {

}

void GravityComponent::update(float dt) {
    float x = gameObject->getComponent<Transform>()->getVelocity().x;
    float y = gameObject->getComponent<Transform>()->getVelocity().y;
    y = y + gravity * dt;
    gameObject->getComponent<Transform>()->setVelocity(x, y);
}