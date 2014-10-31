#include "defines.hpp"
#include "colors.hpp"

#define MAKE_COLOR(r, g, b, a) \
    SDL_Color { (r), (g), (b), (a) }

const SDL_Color Colors::BLACK = MAKE_COLOR(  0,   0,   0, 255);
const SDL_Color Colors::WHITE = MAKE_COLOR(255, 255, 255, 255);
const SDL_Color Colors::RED   = MAKE_COLOR(255,   0,   0, 255);
const SDL_Color Colors::GREEN = MAKE_COLOR(  0, 255,   0, 255);
const SDL_Color Colors::BLUE  = MAKE_COLOR(  0,   0, 255, 255);
const SDL_Color Colors::BROWN = MAKE_COLOR( 64,  13,  18, 255);
const SDL_Color Colors::GRAY  = MAKE_COLOR(119, 119, 119, 255);

SDL_Color Colors::makeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return MAKE_COLOR(r, g, b, a);
}
