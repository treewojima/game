#ifndef __SHIP_HPP__
#define __SHIP_HPP__

#include "defines.hpp"
#include "entity.hpp"
#include "game.hpp"

class Ship : public Entity
{
public:
    Ship(float x_ = 0, float y_ = 0, float vel_x_ = 0, float vel_y_ = 0);
    ~Ship();

    void initializeBody();

    void draw();

    int getWidth() const { return WIDTH; }
    int getHeight() const { return HEIGHT; }

private:
    static const int WIDTH = 20;
    static const int HEIGHT = 20;

    game::EventHandle _eventHandles[4];
};

#endif
