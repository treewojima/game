#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include "defines.hpp"
#include <memory>
#include <SDL2/SDL.h>
#include "texture.hpp"

namespace window
{
    void create(int width, int height);
    void destroy();

    void clear();
    void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    void blit(const Texture &texture);

    void flip();

    SDL_Renderer *getRenderer();
    int getWidth();
    int getHeight();
}

#endif
