#include "src/include/Health.h"
#include "src/include/GameObject.h"
#include "src/include/State.h"

Health::Health() : maxHealth(100), health(maxHealth) {};

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