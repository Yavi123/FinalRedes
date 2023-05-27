#ifndef STATE_H
#define STATE_H

class State
{
public:
    State();
    ~State();
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
};

#endif