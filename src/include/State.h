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
    void AddGameObject(GameObject* obj);
    void DestroyGameObject(GameObject* obj);
protected:
    std::list<GameObject*> gameObjects;
    std::list<GameObject*> toAdd;
    std::list<GameObject*> toDelete;
};

#endif