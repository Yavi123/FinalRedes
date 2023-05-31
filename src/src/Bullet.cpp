#include "src/include/Bullet.h"
#include "src/include/GameObject.h"
#include "src/include/State.h"
#include "src/include/Health.h"

Bullet::Bullet() {
    damage = 10;
    ignore = nullptr;
}
void Bullet::onCollission(GameObject* other) {

    auto otherHealth = other->getComponent<Health>();
    if (otherHealth != ignore) {
        gameObject->context->DestroyGameObject(gameObject);
        if (otherHealth != nullptr) {
            otherHealth->SubstractHealth(damage);
        }
    }
}

void Bullet::SetDamage(uint16_t val) {
    damage = val;
}
void Bullet::SetIgnore(Health* val) {
    ignore = val;
}