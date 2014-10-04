#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__

#include "defines.hpp"
#include <memory>
#include <string>
#include "entity.hpp"
#include "texture.hpp"

class Sprite : public Entity
{
public:
    using Entity::Entity;

    virtual void draw() = 0;
};

class TexturedSprite : public Sprite
{
public:
    TexturedSprite(const std::string &name, std::shared_ptr<Texture> texture);
    virtual ~TexturedSprite();

    void draw();

    inline std::shared_ptr<Texture> getTexture() { return _texture; }

private:
    std::shared_ptr<Texture> _texture;
};

#endif
