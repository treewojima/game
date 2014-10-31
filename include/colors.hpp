#ifndef __COLORS_HPP__
#define __COLORS_HPP__

#include "defines.hpp"
#include <SDL2/SDL.h>

namespace Colors
{
    extern const SDL_Color BLACK;
    extern const SDL_Color WHITE;
    extern const SDL_Color RED;
    extern const SDL_Color GREEN;
    extern const SDL_Color BLUE;
    extern const SDL_Color BROWN;
    extern const SDL_Color GRAY;

    SDL_Color makeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
}

#endif
