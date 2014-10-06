#ifndef __ASTEROID_HPP__
#define __ASTEROID_HPP__

#include "defines.hpp"
#include "entity.hpp"

class Asteroid : public Entity
{
public:
    using Entity::Entity;

    void draw();

    int getWidth() const { return WIDTH; }
    int getHeight() const { return HEIGHT; }

private:
    static const int WIDTH = 40;
    static const int HEIGHT = 40;
};

#endif
