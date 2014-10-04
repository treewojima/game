#include "window.hpp"

#include <cassert>
#include <easylogging++.h>
#include "exception.hpp"
#include "game.hpp"

Window::Window(int width, int height)
{
    LOG(DEBUG) << __FUNCTION__;

    assert(width > 0);
    assert(height > 0);

    _window = SDL_CreateWindow("opengl",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width,
                               height,
                               SDL_WINDOW_SHOWN);
    if (!_window)
        throw SDLException();

    _renderer = SDL_CreateRenderer(_window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer)
    {
        SDL_DestroyWindow(_window);
        throw SDLException();
    }
    else
    {
        SDL_RendererInfo info;
        SDL_GetRendererInfo(_renderer, &info);
        LOG(INFO) << "using renderer \"" << info.name << "\"";
    }
}

Window::~Window()
{
    LOG(DEBUG) << __FUNCTION__;

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void Window::clear()
{
    clear(0, 0, 0, 0);
}

void Window::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint8 old_r, old_g, old_b, old_a;
    SDL_GetRenderDrawColor(_renderer, &old_r, &old_g, &old_b, &old_a);

    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    SDL_RenderClear(_renderer);

    SDL_SetRenderDrawColor(_renderer, old_r, old_g, old_b, old_a);
}

void Window::flip()
{
    SDL_RenderPresent(_renderer);
}
