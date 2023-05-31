//Transform executation
#include "src/include/Transform.h"

Transform::Transform() {
    position = {0,0};
    velocityX = 0;
    velocityY = 0;
}
Transform::Transform(int x, int y) {
    position = {x, y};
    velocityX = 0;
    velocityY = 0;
}
Transform::~Transform() {

}
void Transform::update(float dt) {
    //std::cout << "Transform::update()\n";
    position.x += velocityX * dt;
    position.y += velocityY * dt;
}
void Transform::start() {
    //std::cout << "Transform::start()\n";
}
void Transform::setX(int x) {
    position.x = x;
}
void Transform::setY(int y) {
    position.y = y;
}
SDL_Point Transform::getPosition() {
    return position;
}
float Transform::getVelocityX() {
    return velocityX;
}
float Transform::getVelocityY() {
    return velocityY;
}
void Transform::setVelocity(SDL_Point v) {
    velocityX = v.x;
    velocityY = v.y;
}
void Transform::setVelocity(float x, float y) {
    velocityX = x;
    velocityY = y;
}
void Transform::translate(float x, float y) {
    position.x += x;
    position.y += y;
}
