//Transform executation
#include "src/include/Transform.h"

Transform::Transform() {
    position = {0,0};
    velocity = {0,0};
}
Transform::Transform(float x, float y) {
    position = {x,y};
    velocity = {0,0};
}
Transform::~Transform() {

}
void Transform::update(float dt) {
    //std::cout << "Transform::update()\n";
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}
void Transform::start() {
    //std::cout << "Transform::start()\n";
}


void Transform::setPosition(const Vector2& pos) {
    position = pos;
}
void Transform::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}
Vector2 Transform::getPosition() {
    return position;
}


void Transform::setVelocity(const Vector2& vel) {
    velocity = vel;
}
void Transform::setVelocity(float x, float y) {
    velocity.x = x;
    velocity.y = y;
}
Vector2 Transform::getVelocity() {
    return velocity;
}

void Transform::translate(float x, float y) {
    position.x += x;
    position.y += y;
}
