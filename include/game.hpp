#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "defines.hpp"
#include <functional>
#include <SDL2/SDL.h>
#include <string>

#include "camera.hpp"

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

        // This doesn't quite work as const since the value can't be determined
        // at runtime, so... don't fuck with this!
        static Uint32 CUSTOM_KEYPRESS_EVENT;
    };

    int run(Options options);

    bool isRunning();
    void setRunning(bool b);

    Camera &getCamera();

    Event::Handle registerEvent(SDL_Scancode key,
                                Event::Callback callback,
                                const std::string &debugString = std::string());
    Event::Handle registerEvent(std::shared_ptr<Event> event);
    void unregisterEvent(Event::Handle handle);
}

#endif
