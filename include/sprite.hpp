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
    Sprite(const std::string &name, int x_ = 0, int y_ = 0) :
        Entity(name),
        x(x_),
        y(y_) {}

    virtual void draw() = 0;

    int x, y;
};

class TexturedSprite : public Sprite
{
public:
    TexturedSprite(const std::string &name,
                   std::shared_ptr<Texture> texture,
                   int x_ = 0,
                   int y_ = 0);

    void draw();

    inline std::shared_ptr<Texture> getTexture() { return _texture; }

private:
    std::shared_ptr<Texture> _texture;
};

#endif
