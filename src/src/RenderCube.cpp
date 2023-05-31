//Execute rendercube

#include "src/include/RenderCube.h"
#include "src/include/SDL_Utils.h"
#include "src/include/Transform.h"
#include "src/include/GameObject.h"

RenderCube::RenderCube() {
    color = {255, 255, 255, 255};
    rect = {1,1};
    tr = nullptr;
}

RenderCube::~RenderCube() {
}


void RenderCube::start() {
    tr = gameObject->getTransform();

    rect.x = tr->getPosition().x;
    rect.y = tr->getPosition().y;
    rect.w = 50;
    rect.h = 50;
}

void RenderCube::update(float dt) {
    rect.x = tr->getPosition().x;
    rect.y = tr->getPosition().y;
    SDL_Utils::Instance()->DrawRect(rect, color);
}

void RenderCube::setColor(const SDL_Color& c) {
    color = c;
}
