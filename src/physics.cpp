#include "defines.hpp"
#include "physics.hpp"

#include <Box2D/Box2D.h>
#include <easylogging++.h>
#include <memory>

#include "entity.hpp"
#include "window.hpp"

// Locals
namespace
{
    const b2Vec2 INITIAL_GRAVITY(0, 0);
    const float TIME_STEP = 1.f / 60.f;
    const int VELOCITY_ITERATIONS = 24;
    const int POSITION_ITERATIONS = 8;

    std::unique_ptr<b2World> _world;

    // Global generic contact listener. Assumes that Box2D bodies have
    // a reference Entity for user data.
    class ContactListener : public b2ContactListener
    {
    public:
        void BeginContact(b2Contact *contact)
        {
            auto fixtureA = contact->GetFixtureA();
            auto fixtureB = contact->GetFixtureB();

            // First, try to associate the colliding fixtures with Entities
            auto userData = fixtureA->GetBody()->GetUserData();
            auto entityA = static_cast<Entity *>(userData);
            userData = fixtureB->GetBody()->GetUserData();
            auto entityB = static_cast<Entity *>(userData);

            // Only fire the collision callbacks if both are Entities
            if (entityA != nullptr && entityB != nullptr)
            {
                entityA->startContact(entityB, fixtureB);
                entityB->startContact(entityA, fixtureA);
            }
        }

        void EndContact(b2Contact *contact)
        {
            auto fixtureA = contact->GetFixtureA();
            auto fixtureB = contact->GetFixtureB();

            // First, try to associate the colliding fixtures with Entities
            auto userData = fixtureA->GetBody()->GetUserData();
            auto entityA = static_cast<Entity *>(userData);
            userData = fixtureB->GetBody()->GetUserData();
            auto entityB = static_cast<Entity *>(userData);

            // Only fire the collision callbacks if both are Entities
            if (entityA != nullptr && entityB != nullptr)
            {
                entityA->endContact(entityB, fixtureB);
                entityB->endContact(entityA, fixtureA);
            }
        }
    };

    ContactListener _contactListener;
}

void Physics::initialize()
{
    LOG(INFO) << "using Box2D " << b2_version.major << "." << b2_version.minor
              << "." << b2_version.revision;

    _world = std::unique_ptr<b2World>(new b2World(INITIAL_GRAVITY));
    _world->SetContactListener(&_contactListener);
}

void Physics::step(float dt)
{
    _world->Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}

b2Body *Physics::createBody(const b2BodyDef &bodyDef)
{
    return _world->CreateBody(&bodyDef);
}

void Physics::destroyBody(b2Body *const body)
{
    _world->DestroyBody(body);
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
