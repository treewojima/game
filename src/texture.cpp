#include "defines.hpp"
#include "texture.hpp"

#ifdef _ENABLE_TEXTURES

#include <easylogging++.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include "exception.hpp"
#include "game.hpp"

Texture::Texture(const std::string &filename)
{
    load(filename);
}

Texture::~Texture()
{
    LOG(DEBUG) << __FUNCTION__;

    SDL_DestroyTexture(_texture);
}

void Texture::load(const std::string &filename)
{
    auto surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        std::ostringstream ss;
        ss << "unable to load \"" << filename << "\":" << IMG_GetError();
        throw SDLImageException(ss.str());
    }

    auto texture = SDL_CreateTextureFromSurface(Window::getRenderer(),
                                                surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr)
    {
        std::ostringstream ss;
        ss << "unable to load \"" << filename << "\":" << SDL_GetError();
        throw SDLException(ss.str());
    }
    else
    {
        _texture = texture;
    }
}

#endif
