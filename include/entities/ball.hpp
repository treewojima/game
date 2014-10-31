#ifndef __BALL_HPP__
#define __BALL_HPP__

#include "defines.hpp"
#include "entity.hpp"

class Ball : public CircleEntity
{
public:
    Ball(const b2Vec2 &position);

private:
    static const float DEFAULT_RADIUS;
    static const SDL_Color DEFAULT_COLOR;
};

#endif
