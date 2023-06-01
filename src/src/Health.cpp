#include "src/include/Health.h"
#include "src/include/GameObject.h"
#include "src/include/State.h"
#include "src/include/Transform.h"

Health::Health() : maxHealth(100), health(maxHealth) {
    container = {0, 0, 50, 10};
    gauge = {0, 0, 50, 10};
};

void Health::update(float dt) {
    auto tr = gameObject->getComponent<Transform>();
    container.x = (int)tr->getPosition().x;
    container.y = (int)tr->getPosition().y - 20;
    gauge = {container.x, container.y, 50, 10};

    gauge.w = (int)((float)health / (float)maxHealth * (float)container.w);

    SDL_Utils::Instance()->DrawRect(container, {0, 0, 0, 255});
    SDL_Utils::Instance()->DrawRect(gauge, {0, 255, 0, 255});
    SDL_Utils::Instance()->DrawRect(container, {0, 0, 0, 255}, false);
}

void Health::SetHealth(uint16_t val) {
    maxHealth = val;
    health = val;
}
void Health::SubstractHealth(uint16_t val) {
    int newVal = (int)health - val;

    if (newVal <= 0) {
        gameObject->context->DestroyGameObject(gameObject);
    } else {
        health = newVal;
    }
}