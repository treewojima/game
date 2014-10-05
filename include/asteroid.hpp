#ifndef __ASTEROID_HPP__
#define __ASTEROID_HPP__

#include "defines.hpp"
#include "sprite.hpp"

class Asteroid : public Sprite
{
public:
    using Sprite::Sprite;

    void draw();

    int getWidth() const { return WIDTH; }
    int getHeight() const { return HEIGHT; }

private:
    static const int WIDTH = 40;
    static const int HEIGHT = 40;
};

#endif
