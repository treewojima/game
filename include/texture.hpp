#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include "defines.hpp"
#include <SDL2/SDL.h>
#include <string>
#include "exception.hpp"

#ifdef _ENABLE_TEXTURES

class Texture
{
public:
    Texture(const std::string &filename);
    ~Texture();

    void load(const std::string &filename);

    inline SDL_Texture *getRawTexture() const { return _texture; }

    inline int getWidth() const
    {
        int w = 0;
        if (SDL_QueryTexture(getRawTexture(), nullptr, nullptr, &w, nullptr))
            throw SDLException();
        return w;
    }

    inline int getHeight() const
    {
        int h = 0;
        if (SDL_QueryTexture(getRawTexture(), nullptr, nullptr, nullptr, &h))
            throw SDLException();
        return h;
    }

private:
    SDL_Texture *_texture;
};

#endif

#endif
