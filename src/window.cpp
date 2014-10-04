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

    auto rendererFlags = SDL_RENDERER_ACCELERATED |
                         SDL_RENDERER_PRESENTVSYNC |
                         SDL_RENDERER_TARGETTEXTURE;
    _renderer = SDL_CreateRenderer(_window, -1, rendererFlags);
    if (_renderer == nullptr)
    {
        SDL_DestroyWindow(_window);
        throw SDLException();
    }
    else
    {
        SDL_RendererInfo info;
        SDL_GetRendererInfo(_renderer, &info);
        bool vsync = info.flags & SDL_RENDERER_PRESENTVSYNC;
        bool targetTexture = info.flags & SDL_RENDERER_TARGETTEXTURE;

        std::ostringstream ss;
        ss << "using renderer \"" << info.name << "\"";
        ss << " (vsync " << (vsync ? "enabled" : "disabled") << ")";
        ss << " (rendering to texture " << (targetTexture ? "enabled" : "disabled") << ")";

        LOG(INFO) << ss.str();
    }
}

void window::destroy()
{
    LOG(DEBUG) << __FUNCTION__;

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

void window::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    SDL_RenderClear(_renderer);
}

void window::blit(const Texture &texture, int x, int y)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
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

void window::setTitle(const std::string &title)
{
    SDL_SetWindowTitle(_window, title.c_str());
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
