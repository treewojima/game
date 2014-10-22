#include "window.hpp"

#include <cassert>
#include <easylogging++.h>
#include "exception.hpp"
#include "game.hpp"
#include "physics.hpp"

// Locals
namespace
{
    SDL_Window *_window;
    SDL_Renderer *_renderer;
}

void Window::create(int width, int height)
{
    assert(width > 0);
    assert(height > 0);

    _window = SDL_CreateWindow("sdl",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width,
                               height,
                               SDL_WINDOW_SHOWN);
    if (_window == nullptr)
        throw SDLException();

    LOG(INFO) << "created window (width = " << width
              << ", height = " << height << ")";

    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED |
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

        LOG(INFO) << "using renderer \"" << info.name << "\" "
                  << "(vsync " << (vsync ? "enabled" : "disabled") << ", "
                  << "rendering to texture "
                  << (targetTexture ? "enabled" : "disabled") << ")";
    }
}

void Window::destroy()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    LOG(INFO) << "destroyed window";
}

void Window::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    SDL_RenderClear(_renderer);
}

void Window::blitTexture(const Texture &texture, int x, int y)
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

void Window::flip()
{
    SDL_RenderPresent(_renderer);
}

void Window::setTitle(const std::string &title)
{
    SDL_SetWindowTitle(_window, title.c_str());
}

SDL_Renderer *Window::getRenderer()
{
    return _renderer;
}

int Window::getWidth()
{
    int w;
    SDL_GetWindowSize(_window, &w, nullptr);
    return w;
}

int Window::getHeight()
{
    int h;
    SDL_GetWindowSize(_window, nullptr, &h);
    return h;
}

float Window::getWidthMeters()
{
    return getWidth() * Physics::PIXELS_TO_METERS;
}

float Window::getHeightMeters()
{
    return getHeight() * Physics::PIXELS_TO_METERS;
}
