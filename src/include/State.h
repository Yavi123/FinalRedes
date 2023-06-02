#ifndef STATE_H
#define STATE_H
#include <list>
#include "src/include/GameObject.h"
class CollissionManager;
class StateMachine;
class Message;
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

    GameObject* GetGameObjectById(u_int16_t id);

    virtual void HandleMessage(const Message& msg) = 0;

    void SetContext(StateMachine* machine) { stMachine = machine;};
    StateMachine* GetContext() { return stMachine;};
protected:
    std::list<GameObject*> gameObjects;
    CollissionManager* colman;
    std::list<GameObject*> toAdd;
    std::list<GameObject*> toDelete;

    StateMachine* stMachine;
};

#endif