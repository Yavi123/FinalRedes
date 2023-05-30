#ifndef STATE_H
#define STATE_H
#include <list>

class GameObject;
class State
{
public:
    State();
    ~State();
    virtual void Init() = 0;
    void Update(float deltaTime);
private:
    std::list<GameObject*> gameObjects;
};

#endif