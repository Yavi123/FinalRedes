//Draw a rect cube
#ifndef SHOOTING_H
#define SHOOTING_H

#include "Component.h"

class Shooting: public Component
{
public:
    __CMPID_DECL__(CMP_SHOOTING)
    Shooting();
    ~Shooting();
    void update(float dt) override;
    void start() override;
    void awake(){};
private:
};

#endif