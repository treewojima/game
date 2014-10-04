#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include "defines.hpp"
#include <GL/glew.h>
#include <SDL2/SDL.h>

class Window
{
public:
    Window(int width, int height);
    ~Window();

    void clear();
    void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    void flip();

    inline SDL_Renderer *getRenderer() { return _renderer; }

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
};

#endif
