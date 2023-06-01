#ifndef BULLET_H
#define BULLET_H
#include "Component.h"
#include "ECSDefs.h"

class Health;

class Bullet : public Component
{
public:
    __CMPID_DECL__(CMP_BULLET)
    Bullet();
    ~Bullet() = default;
    void update(float dt) override;
    void start() override {};
    void awake(){};
    void onCollission(GameObject* other) override;

    void SetDamage(uint16_t val);
    void SetIgnore(Health* val);
private:
    uint16_t damage;
    Health* ignore;
};

#endif