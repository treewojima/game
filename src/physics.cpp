#include "defines.hpp"
#include "physics.hpp"

#include <Box2D/Box2D.h>
#include <easylogging++.h>
#include <memory>

#include "window.hpp"

const float Physics::METERS_TO_PIXELS = 50.f;
const float Physics::PIXELS_TO_METERS = 1.f / Physics::METERS_TO_PIXELS;

// Locals
namespace
{
    const b2Vec2 INITIAL_GRAVITY(0, -2);
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

b2Vec2 Physics::getOriginOffset()
{
    float offsetX = Window::getWidth() / 2;
    float offsetY = Window::getHeight() / 2;
    return b2Vec2(offsetX, offsetY);
}
