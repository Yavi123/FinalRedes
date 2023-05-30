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
    void Start();
    void Update(float deltaTime);
protected:
    std::list<GameObject*> gameObjects;
};

#endif