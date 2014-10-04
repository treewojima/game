#include "window.hpp"

#include <cassert>
#include <easylogging++.h>
#include "exception.hpp"
#include "game.hpp"

static SDL_Window *_window;
static SDL_Renderer *_renderer;

void window::create(int width, int height)
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
    if (_window == nullptr)
        throw SDLException();

    _renderer = SDL_CreateRenderer(_window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr)
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

void window::destroy()
{
    LOG(DEBUG) << __FUNCTION__;

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void window::clear()
{
    window::clear(0, 0, 0, 0);
}

void window::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint8 old_r, old_g, old_b, old_a;
    SDL_GetRenderDrawColor(_renderer, &old_r, &old_g, &old_b, &old_a);

    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    SDL_RenderClear(_renderer);

    SDL_SetRenderDrawColor(_renderer, old_r, old_g, old_b, old_a);
}

void window::blit(const Texture &texture)
{
    SDL_Rect r;
    r.x = r.y = 0;
    r.w = texture.getWidth();
    r.h = texture.getHeight();

    SDL_RenderCopy(_renderer,
                   texture.getRawTexture(),
                   nullptr,
                   &r);
}

void window::flip()
{
    SDL_RenderPresent(_renderer);
}

SDL_Renderer *window::getRenderer()
{
    return _renderer;
}

int window::getWidth()
{
    int w;
    SDL_GetWindowSize(_window, &w, nullptr);
    return w;
}

int window::getHeight()
{
    int h;
    SDL_GetWindowSize(_window, nullptr, &h);
    return h;
}
