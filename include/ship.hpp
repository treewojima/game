#ifndef __SHIP_HPP__
#define __SHIP_HPP__

#include "defines.hpp"
#include "game.hpp"
#include "sprite.hpp"

class Ship : public Sprite
{
public:
    Ship(int x_ = 0, int y_ = 0);
    ~Ship();

    void draw();

private:
    game::EventHandle _eventHandles[4];
};

#endif
