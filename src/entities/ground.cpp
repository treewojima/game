#include "defines.hpp"
#include "entities/ground.hpp"
#include "physics.hpp"

const float Ground::DEFAULT_HEIGHT = 20 * Physics::PIXELS_TO_METERS;

void Ground::draw()
{
    auto r = getSDLRect();
    auto renderer = Window::getRenderer();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &r);
}
