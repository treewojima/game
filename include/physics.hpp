#ifndef __PHYSICS_HPP__
#define __PHYSICS_HPP__

#include "defines.hpp"
#include <Box2D/Box2D.h>
#include <easylogging++.h>

namespace Physics
{
    extern const float METERS_TO_PIXELS;
    extern const float PIXELS_TO_METERS;

    void initialize();
    void step(float dt);

    b2World &getWorld();
}

// Helper stream operators for b2Vec2
template <class T>
inline std::ostream &operator<<(std::ostream &stream, const b2Vec2 &v)
{
    stream << "b2Vec2(" << v.x << ", " << v.y << ")";
    return stream;
}

inline MAKE_LOGGABLE(b2Vec2, v, stream)
{
    stream << "b2Vec2(" << v.x << ", " << v.y << ")";
    return stream;
}

#endif
