#ifndef __PADDLE_HPP__
#define __PADDLE_HPP__

#include "defines.hpp"
#include "entity.hpp"
#include "game.hpp"

class Paddle : public BoxEntity
{
public:
    Paddle(const b2Vec2 &position);
    ~Paddle();

    void initialize();

private:
    static const float DEFAULT_WIDTH;
    static const float DEFAULT_HEIGHT;
    static const SDL_Color DEFAULT_COLOR;

    enum { PADDLE_LEFT, PADDLE_RIGHT, NUM_PADDLE_EVENTS };
    Game::Event::Handle _eventHandles[NUM_PADDLE_EVENTS];
};

#endif
