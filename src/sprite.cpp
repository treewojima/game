#include "sprite.hpp"

#include <easylogging++.h>
#include <cassert>
#include "window.hpp"

TexturedSprite::TexturedSprite(const std::string &name,
                               std::shared_ptr<Texture> texture) :
    Sprite(name),
    _texture(texture)
{
     assert(_texture.get() != nullptr);
}

TexturedSprite::~TexturedSprite()
{
}

void TexturedSprite::draw()
{
    window::blit(*_texture);
}
