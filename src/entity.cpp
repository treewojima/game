#include "defines.hpp"
#include "entity.hpp"

#include <cassert>
#include <cmath>
#include <easylogging++.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <sstream>
#include "physics.hpp"

// Locals
namespace
{
    // Global generic contact listener. Assumes that Box2D bodies only have
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

Entity::Entity(const std::string &name, Type type) :
    _name(name),
    _type(type)
{
    Physics::getWorld().SetContactListener(&_contactListener);
}

Entity::~Entity()
{
    LOG(DEBUG) << "destroyed entity " << getName();
}

std::string Entity::toString() const
{
    std::ostringstream ss;
    ss << "Entity[name = \"" << getName() << "\"]";
    return ss.str();
}
