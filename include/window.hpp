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

    void clear(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0);
    void blit(const Texture &texture, int x, int y);
    void flip();

    void setTitle(const std::string &title);

    SDL_Renderer *getRenderer();
    int getWidth();
    int getHeight();
}

#endif
