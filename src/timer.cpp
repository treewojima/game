#include "defines.hpp"
#include "timer.hpp"

#include <easylogging++.h>
#include <SDL2/SDL.h>

Timer::Timer() :
    _startTicks(0),
    _pausedTicks(0),
    _state(State::STOPPED)
{
}

Timer::~Timer()
{
    // This serves no purpose other than to print the debug message
    //stop();
}

void Timer::start()
{
    _state = State::RUNNING;
    _startTicks = SDL_GetTicks();
    _pausedTicks = 0;

    //LOG(DEBUG) << "starting timer";
}

void Timer::stop()
{
    //LOG(DEBUG) << "stopped timer after " << getTicks() << " ticks";

    _state = State::STOPPED;
    _startTicks = _pausedTicks = 0;
}

void Timer::pause()
{
    if (_state != State::RUNNING)
    {
        LOG(WARNING) << "tried to pause non-running timer";
    }
    else
    {
        _state = State::PAUSED;
        _pausedTicks = SDL_GetTicks() - _startTicks;
        _startTicks = 0;

        LOG(DEBUG) << "pausing timer at " << getTicks() << " ticks";
    }
}

void Timer::resume()
{
    if (_state != State::PAUSED)
    {
        LOG(WARNING) << "tried to resume non-paused timer";
    }
    else
    {
        _state = State::RUNNING;
        _startTicks = SDL_GetTicks() - _pausedTicks;
        _pausedTicks = 0;

        LOG(DEBUG) << "resuming timer at " << getTicks() << " ticks";
    }
}

long Timer::getTicks() const
{
    long time = 0;

    switch (_state)
    {
    case State::STOPPED:
        break;

    case State::RUNNING:
        time = SDL_GetTicks() - _startTicks;
        break;

    case State::PAUSED:
        time = _pausedTicks;
    }

    return time;
}
