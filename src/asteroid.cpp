#include "defines.hpp"
#include "asteroid.hpp"

#include <easylogging++.h>
#include <SDL2/SDL.h>
#include "window.hpp"

void Asteroid::draw()
{
    SDL_Rect r = getBoundingBox();
    SDL_SetRenderDrawColor(window::getRenderer(), 255, 255, 255, 0);
    SDL_RenderFillRect(window::getRenderer(), &r);
}
