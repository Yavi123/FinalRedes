//Transform executation
#include "src/include/Transform.h"

Transform::Transform() {
    position = {0,0};
    velocity = {0,0};
}
Transform::Transform(int x, int y) {
    position = {x, y};
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
void Transform::setX(int x) {
    position.x = x;
}
void Transform::setY(int y) {
    position.y = y;
}
SDL_Point Transform::getPosition() {
    return position;
}
SDL_Point Transform::getVelocity() {
    return velocity;
}
void Transform::setVelocity(SDL_Point v) {
    velocity = v;
}
void Transform::setVelocity(int x, int y) {
    velocity.x = x;
    velocity.y = y;
}
