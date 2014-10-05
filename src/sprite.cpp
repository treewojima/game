#include "sprite.hpp"

#include <easylogging++.h>
#include <cassert>
#include "window.hpp"

TexturedSprite::TexturedSprite(const std::string &name,
                               std::shared_ptr<Texture> texture,
                               float x_, float y_,
                               float vel_x_, float vel_y_) :
    Sprite(name, x_, y_, vel_x_, vel_y_),
    _texture(texture)
{
     assert(_texture.get() != nullptr);
}

void TexturedSprite::draw()
{
    window::blit(*_texture,
                 static_cast<int>(x),
                 static_cast<int>(y));
}
