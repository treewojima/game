#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include "defines.hpp"
#include <SDL2/SDL.h>

class Timer
{
public:
    enum class State
    {
        STOPPED,
        RUNNING,
        PAUSED
    };

    Timer();
    ~Timer();

    void start();
    void stop();
    void pause();
    void resume();

    Uint32 getTicks() const;
    inline State getState() const { return _state; }

private:
    Uint32 _startTicks;
    Uint32 _pausedTicks;
    State _state;
};

#endif
