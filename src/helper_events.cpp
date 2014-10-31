#include "defines.hpp"
#include "helper_events.hpp"

#include <easylogging++.h>
#include <iostream>

bool Game::KeyEvent::test(const SDL_Event &e)
{
    //return (e.type == SDL_KEYDOWN &&
    //        e.key.keysym.sym == _key);
    return (e.type == CUSTOM_KEYPRESS_EVENT &&
            static_cast<const Uint8 *>(e.user.data1)[_key]);
}

void Game::KeyEvent::fire(const SDL_Event &e)
{
    _callback(e);
}

bool Game::QuitEvent::test(const SDL_Event &e)
{
    return (e.type == SDL_QUIT);
}

void Game::QuitEvent::fire(const SDL_Event &e)
{
    Game::setRunning(false);
    LOG(INFO) << "received quit signal";
}
