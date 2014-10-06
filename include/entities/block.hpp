#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include "defines.hpp"
#include "entity.hpp"

class Block : public Entity
{
public:
    using Entity::Entity;

    void draw();

    int getWidth() const { return DEFAULT_WIDTH; }
    int getHeight() const { return DEFAULT_HEIGHT; }

    static const int DEFAULT_WIDTH = 80;
    static const int DEFAULT_HEIGHT = 20;
};

#endif
