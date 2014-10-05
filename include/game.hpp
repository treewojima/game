#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "defines.hpp"
#include <functional>
#include <SDL2/SDL.h>
#include <string>
#include "entity.hpp"
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
        Event(const std::string &debugString_ = std::string()) :
            debugString(debugString_) {}
        virtual ~Event() {}

        virtual bool test(const SDL_Event &e) = 0;
        virtual void fire() = 0;

        std::string debugString;
    };

    int run(Options options);

    bool isRunning();
    void setRunning(bool b);

    typedef std::function<void ()> EventCallback;
    typedef int EventHandle;
    EventHandle registerEvent(SDL_Keycode key,
                              EventCallback callback,
                              const std::string &debugString = std::string());
    EventHandle registerEvent(std::shared_ptr<Event> event);
    void unregisterEvent(EventHandle handle);

    void registerCollidable(std::shared_ptr<Entity> entity);
}

#endif
