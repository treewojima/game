#include "defines.hpp"
#include "timer.hpp"

#include <easylogging++.h>

Timer::Timer() :
    _startTicks(0),
    _pausedTicks(0),
    _state(TimerState::STOPPED)
{
}

Timer::~Timer()
{
    // This serves no purpose other than to print the debug message
    //stop();
}

void Timer::start()
{
    _state = TimerState::RUNNING;
    _startTicks = SDL_GetTicks();
    _pausedTicks = 0;

    LOG(DEBUG) << "starting timer";
}

void Timer::stop()
{
    LOG(DEBUG) << "stopped timer after " << getTicks() << " ticks";

    _state = TimerState::STOPPED;
    _startTicks = _pausedTicks = 0;
}

void Timer::pause()
{
    if (_state != TimerState::RUNNING)
    {
        LOG(WARNING) << "tried to pause non-running timer";
    }
    else
    {
        _state = TimerState::PAUSED;
        _pausedTicks = SDL_GetTicks() - _startTicks;
        _startTicks = 0;

        LOG(DEBUG) << "pausing timer at " << getTicks() << " ticks";
    }
}

void Timer::resume()
{
    if (_state != TimerState::PAUSED)
    {
        LOG(WARNING) << "tried to resume non-paused timer";
    }
    else
    {
        _state = TimerState::RUNNING;
        _startTicks = SDL_GetTicks() - _pausedTicks;
        _pausedTicks = 0;

        LOG(DEBUG) << "resuming timer at " << getTicks() << " ticks";
    }
}

Uint32 Timer::getTicks() const
{
    Uint32 time = 0;

    switch (_state)
    {
    case TimerState::STOPPED:
        break;

    case TimerState::RUNNING:
        time = SDL_GetTicks() - _startTicks;
        break;

    case TimerState::PAUSED:
        time = _pausedTicks;
    }

    return time;
}
