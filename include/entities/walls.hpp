#ifndef __WALLS_HPP__
#define __WALLS_HPP__

#include "defines.hpp"
#include "entity.hpp"

class Walls : public Entity
{
    friend class Paddle;
    friend class Ball;

public:
    Walls();
    ~Walls();

    void draw() {}

private:
    b2Body *_body;
    b2Fixture *_bottomFixture;
};

#endif
