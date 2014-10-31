#include "defines.hpp"
#include "entities/ball.hpp"

const float Ball::DEFAULT_RADIUS = 0.125;
const SDL_Color Ball::DEFAULT_COLOR = { 255, 0, 0, 0 };

Ball::Ball(const b2Vec2 &position) : CircleEntity("Ball",
                                                  position,
                                                  DEFAULT_RADIUS,
                                                  DEFAULT_COLOR)
{
}
