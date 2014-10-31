#include "defines.hpp"
#include "physics.hpp"

#include <Box2D/Box2D.h>
#include <easylogging++.h>
#include <memory>

#include "window.hpp"

// Locals
namespace
{
    const b2Vec2 INITIAL_GRAVITY(0, -4);
    const float TIME_STEP = 1.f / 60.f;
    const int VELOCITY_ITERATIONS = 6;
    const int POSITION_ITERATIONS = 2;

    std::unique_ptr<b2World> _world;
}

void Physics::initialize()
{
    LOG(INFO) << "using Box2D " << b2_version.major << "." << b2_version.minor
              << "." << b2_version.revision;

    _world = std::unique_ptr<b2World>(new b2World(INITIAL_GRAVITY));
}

void Physics::step(float dt)
{
    _world->Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}

b2World &Physics::getWorld()
{
    return *_world;
}

b2Vec2 Physics::getGravity()
{
    return _world->GetGravity();
}

void Physics::setGravity(const b2Vec2 &gravity)
{
    _world->SetGravity(gravity);
}
