#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "defines.hpp"
#include <easylogging++.h>
#include <functional>
#include <SDL2/SDL.h>
#include "window.hpp"

namespace game
{
    struct Options
    {
        int windowWidth, windowHeight;
    };

    class Event
    {
    public:
        virtual ~Event() { LOG(DEBUG) << __FUNCTION__; }

        virtual bool test(const SDL_Event &e) = 0;
        virtual void fire() = 0;
    };

    int run(Options options);

    bool isRunning();
    void setRunning(bool b);

    typedef std::function<void ()> EventCallback;
    void registerEvent(SDL_Keycode key, EventCallback callback);
    void registerEvent(Event *event);
}

#endif
