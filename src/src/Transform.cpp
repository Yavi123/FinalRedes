//Transform executation
#include "src/include/Transform.h"
#include "src/include/NetManager.h"
#include "src/include/Redes/Message.h"

Transform::Transform() : Transform(0, 0) {}

Transform::Transform(float x, float y) {
    position = {x,y};
    velocity = {0,0};
    size = {50,50};
    rotation = 0;
}
Transform::~Transform() {

}
void Transform::update(float dt) {
    //std::cout << "Transform::update()\n";
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    if(velocity.getX() == 0 && velocity.getY() == 0) return;
    TransformMessage msg(gameObject->id, position, rotation);
    NetManager::Instance()->SendMessage(msg);
}
void Transform::start() {
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

void Transform::setSize(const Vector2& siz) {
    size = siz;
}
void Transform::setSize(float x, float y) {
    size.x = x;
    size.y = y;
}
Vector2 Transform::getSize() {
    return size;
}


float Transform::getRotation(){
    return rotation;
}
void Transform::setRotation(float r){
    rotation = r;
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
