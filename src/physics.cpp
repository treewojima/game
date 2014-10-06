#include "defines.hpp"
#include "physics.hpp"

#include <Box2D/Box2D.h>
#include <easylogging++.h>
#include <memory>

static const b2Vec2 INITIAL_GRAVITY(0, 10);
static const float TIME_STEP = 1.0f / 60.0f;
static const int VELOCITY_ITERATIONS = 6;
static const int POSITION_ITERATIONS = 2;

static std::unique_ptr<b2World> _world;

void physics::init()
{
    LOG(INFO) << "using Box2D " << b2_version.major << "." << b2_version.minor
              << "." << b2_version.revision;

    _world = std::unique_ptr<b2World>(new b2World(INITIAL_GRAVITY));
}

void physics::step(float dt)
{
    getWorld().Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}

void physics::shutdown()
{
    LOG(DEBUG) << __FUNCTION__;

    _world.reset();
}

b2World &physics::getWorld()
{
    return *_world;
}
