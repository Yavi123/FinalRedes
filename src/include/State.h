#ifndef STATE_H
#define STATE_H
#include <list>
class CollissionManager;
class GameObject;
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