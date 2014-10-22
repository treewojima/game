#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "defines.hpp"
#include <functional>
#include <SDL2/SDL.h>
#include <string>
#include "entity.hpp"
#include "window.hpp"

namespace Game
{
    struct Options
    {
        int windowWidth, windowHeight;
    };

    class Event
    {
    public:
        typedef int Handle;
        typedef std::function<void (const SDL_Event &e)> Callback;

        Event(const std::string &debugString_ = std::string()) :
            debugString(debugString_) {}
        virtual ~Event()
        {
#ifdef _DEBUG_EVENTS
            LOG(DEBUG) << "destroyed event \"" << debugString << "\"";
#endif
        }

        virtual bool test(const SDL_Event &e) = 0;
        virtual void fire(const SDL_Event &e) = 0;

        std::string debugString;        
    };

    int run(Options options);

    bool isRunning();
    void setRunning(bool b);

    Event::Handle registerEvent(SDL_Keycode key,
                              Event::Callback callback,
                              const std::string &debugString = std::string());
    Event::Handle registerEvent(std::shared_ptr<Event> event);
    void unregisterEvent(Event::Handle handle);
}

#endif
