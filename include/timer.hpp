#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include "defines.hpp"
#include <SDL2/SDL.h>

enum class TimerState
{
    STOPPED,
    RUNNING,
    PAUSED
};

class Timer
{
public:
    Timer();
    ~Timer();

    void start();
    void stop();
    void pause();
    void resume();

    Uint32 getTicks() const;
    inline TimerState getState() const { return _state; }

private:
    Uint32 _startTicks;
    Uint32 _pausedTicks;
    TimerState _state;
};

#endif
