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
    virtual ~Sprite() {}

    virtual void draw() = 0;
};

class TexturedSprite : public Sprite
{
public:
    TexturedSprite(const std::string &name,
                   std::shared_ptr<Texture> texture,
                   float x_ = 0, float y_ = 0,
                   float vel_x_ = 0, float vel_y_ = 0);

    void draw();

    int getWidth() const { return getTexture()->getWidth(); }
    int getHeight() const { return getTexture()->getHeight(); }

    inline std::shared_ptr<Texture> getTexture() const { return _texture; }

private:
    std::shared_ptr<Texture> _texture;
};

#endif
