//Playing state
#ifndef PLAYING_H
#define PLAYING_H
#include "State.h"
#include "SDL_rect.h"

class Playing : public State
{
public:
    Playing();
    ~Playing();
    void Init() override;
};

#endif
