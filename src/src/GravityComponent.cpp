//Executes GravityComponent.h

#include "src/include/GravityComponent.h"
#include "src/include/GameObject.h"
#include "src/include/Transform.h"

GravityComponent::GravityComponent() {
    gravity = 0.0f;
}
GravityComponent::GravityComponent(float g) {
    gravity = g;
}

GravityComponent::~GravityComponent() {

}

void GravityComponent::update(float dt) {
    //std::cout << "GravityComponent::update()\n";  
    int x = gameObject->getComponent<Transform>()->getVelocity().x;
    int y = gameObject->getComponent<Transform>()->getVelocity().y;
    y += gravity*dt;
    gameObject->getComponent<Transform>()->setVelocity(x, y);
}