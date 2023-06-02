//Playing state
#ifndef PLAYING_H
#define PLAYING_H
#include "State.h"
#include "SDL_rect.h"

class CollissionManager;
class Playing : public State
{
public:
    Playing();
    ~Playing();
    void Init() override;
    void HandleMessage(const Message& msg) override;
    GameObject* controlled;  
};

#endif
