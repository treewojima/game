#ifndef __HELPER_EVENTS_HPP__
#define __HELPER_EVENTS_HPP__

#include "defines.hpp"
#include "game.hpp"

namespace Game
{
    // Helper key handler event for registerEvent()
    class KeyEvent : public Event
    {
    public:
        KeyEvent(SDL_Scancode key,
                 Event::Callback callback,
                 const std::string debugString_) :
            Event(debugString_),
            _key(key),
            _callback(callback) {}

        bool test(const SDL_Event &e);
        void fire(const SDL_Event &e);

    private:
        SDL_Scancode _key;
        Game::Event::Callback _callback;
    };

    // Program quit handling event, for signals such as ^C
    class QuitEvent : public Event
    {
    public:
        QuitEvent() : Event("QuitEvent") {}

        bool test(const SDL_Event &e);
        void fire(const SDL_Event &e);
    };
}

#endif
