#ifndef __PHYSICS_HPP__
#define __PHYSICS_HPP__

#include "defines.hpp"
#include <Box2D/Box2D.h>

namespace physics
{
    void init();
    void step(float dt);
    void shutdown();

    b2World &getWorld();
}

#endif
