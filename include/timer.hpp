#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include "defines.hpp"

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

    long getTicks() const;
    inline State getState() const { return _state; }

private:
    long _startTicks;
    long _pausedTicks;
    State _state;
};

#endif
