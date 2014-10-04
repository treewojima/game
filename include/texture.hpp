#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include "defines.hpp"
#include <memory>
#include <SDL2/SDL.h>
#include <string>

class Texture
{
public:
    Texture(const std::string &filename);
    ~Texture();

    void load(const std::string &filename);

    inline SDL_Texture *getRawTexture() { return _texture.get(); }

private:
    std::shared_ptr<SDL_Texture> _texture;
};

#endif

