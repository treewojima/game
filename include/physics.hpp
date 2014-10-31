#ifndef __PHYSICS_HPP__
#define __PHYSICS_HPP__

#include "defines.hpp"
#include <Box2D/Box2D.h>
#include <easylogging++.h>

namespace Physics
{
    void initialize();
    void step(float dt);

    b2World &getWorld();

    b2Vec2 getGravity();
    void setGravity(const b2Vec2 &gravity);
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
