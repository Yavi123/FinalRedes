#ifndef HEALTH_H_
#define HEALTH_H_
#include "Component.h"
#include "ECSDefs.h"

class Health : public Component
{
public:
    __CMPID_DECL__(CMP_HEALTH)
    Health();
    ~Health() = default;
    void update(float dt) override {};
    void start() override {};
    void awake(){};

    void SetHealth(uint16_t val);
    void SubstractHealth(uint16_t val);
private:
    uint16_t maxHealth;
    uint16_t health;
};

#endif