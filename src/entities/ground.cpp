#include "defines.hpp"
#include "entities/ground.hpp"
#include "physics.hpp"

#ifdef _ENABLE_GROUND

const float Ground::DEFAULT_HEIGHT = 0.5;

/*void Ground::draw()
{
    auto r = getSDLRect();
    auto renderer = Window::getRenderer();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &r);
}*/

#endif
