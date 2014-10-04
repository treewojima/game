#include "texture.hpp"

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

    // No need to clean up the SDL_Texture here, since there's a custom deleter
    // passed to the shared_ptr that does it for us
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

    auto texture = SDL_CreateTextureFromSurface(game::getWindow().getRenderer(),
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
        auto deleter = [](SDL_Texture *t)
        {
            LOG(DEBUG) << __FUNCTION__;
            SDL_DestroyTexture(t);
        };

        _texture = std::shared_ptr<SDL_Texture>(texture, deleter);
    }
}
