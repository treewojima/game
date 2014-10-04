#include "sprite.hpp"

#include <easylogging++.h>
#include <cassert>
#include "window.hpp"

TexturedSprite::TexturedSprite(const std::string &name,
                               std::shared_ptr<Texture> texture,
                               int x_, int y_) :
    Sprite(name, x_, y_),
    _texture(texture)
{
     assert(_texture.get() != nullptr);
}

void TexturedSprite::draw()
{
    window::blit(*_texture, x, y);
}
