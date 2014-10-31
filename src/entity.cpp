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
    class ContactListener : public b2ContactListener
    {
    public:
        void BeginContact(b2Contact *contact)
        {
            //check if fixture A was a ball
            auto userData = contact->GetFixtureA()->GetBody()->GetUserData();
            if (userData != nullptr)
                static_cast<Entity *>(userData)->startContact();

            //check if fixture B was a ball
            userData = contact->GetFixtureB()->GetBody()->GetUserData();
            if (userData != nullptr)
              static_cast<Entity *>(userData)->startContact();
        }

        void EndContact(b2Contact *contact)
        {
            //check if fixture A was a ball
            auto userData = contact->GetFixtureA()->GetBody()->GetUserData();
            if (userData != nullptr)
                static_cast<Entity *>(userData)->endContact();

            //check if fixture B was a ball
            userData = contact->GetFixtureB()->GetBody()->GetUserData();
            if (userData != nullptr)
              static_cast<Entity *>(userData)->endContact();
        }
    };

    ContactListener _contactListener;
}

Entity::Entity(const std::string &name) :
    _name(name)
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

BoxEntity::BoxEntity(const std::string &name,
                     const b2Vec2 &position,
                     const b2Vec2 &dimensions,
                     const SDL_Color &color,
                     bool filled) :
    Entity(name),
    _body(nullptr),
    _dimensions(dimensions),
    _color(color),
    _filled(filled)
{
    // First, create the body itself
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = b2_dynamicBody;
    _body = Physics::createBody(bodyDef);

    // Now create the body fixture
    b2PolygonShape box;
    box.SetAsBox(dimensions.x / 2, dimensions.y / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1;
    fixtureDef.friction = 0;
    fixtureDef.restitution = 1;
    _body->CreateFixture(&fixtureDef);
}

BoxEntity::~BoxEntity()
{
    assert(_body != nullptr);
    Physics::destroyBody(_body);
}

void BoxEntity::draw()
{
    auto position = getPosition();
    auto dimensions = getDimensions();

    // Adjust for coordinates origin
    position.x -= dimensions.x / 2.f;
    position.y -= dimensions.y / 2.f;

    glColor4ub(_color.r, _color.g, _color.b, _color.a);

    if (_filled)
    {
        // Draw a filled rectangle
        glRectf(position.x,
                position.y,
                position.x + dimensions.x,
                position.y + dimensions.y);
    }
    else
    {
        // Draw a wireframe rectangle
        glBegin(GL_LINE_LOOP);
        {
            glVertex2f(position.x, position.y);
            glVertex2f(position.x + dimensions.x, position.y);
            glVertex2f(position.x + dimensions.x, position.y + dimensions.y);
            glVertex2f(position.x, position.y + dimensions.y);
        }
        glEnd();
    }
}

std::string BoxEntity::toString() const
{
    std::ostringstream ss;
    ss << "BoxEntity[name = \"" << getName() << "\", position = "
       << getPosition() << ", dimensions = " << getDimensions() << "]";
    return ss.str();
}

CircleEntity::CircleEntity(const std::string &name,
                           const b2Vec2 &position,
                           float radius,
                           const SDL_Color &color,
                           bool filled) :
    Entity(name),
    _body(nullptr),
    _radius(radius),
    _color(color),
    _filled(filled)
{
    // First, create the body itself
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = b2_dynamicBody;
    _body = Physics::createBody(bodyDef);

    // Now create the body fixture
    b2CircleShape shape;
    shape.m_radius = radius;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0;
    fixtureDef.restitution = 1;
    _body->CreateFixture(&fixtureDef);
}

CircleEntity::~CircleEntity()
{
    assert(_body != nullptr);
    Physics::destroyBody(_body);
}

void CircleEntity::draw()
{
    auto position = getPosition();
    auto radius = getRadius();

    glColor4ub(_color.r, _color.g, _color.b, _color.a);

    // Draw either filled triangles or wireframe
    glBegin(_filled ? GL_TRIANGLE_FAN : GL_LINE_LOOP);
    {
        // If filling, set the center vertex
        if (_filled) glVertex2f(position.x, position.y);

        // Adjust the stepping for more/less precision (should be a factor
        // of 360)
        const int STEP = 20;
        for (int angle = 0; angle <= 360; angle += STEP)
        {
            glVertex2f(position.x + std::sin(angle * (M_PI / 180)) * radius,
                       position.y + std::cos(angle * (M_PI / 180)) * radius);
        }
    }
    glEnd();
}

std::string CircleEntity::toString() const
{
    std::ostringstream ss;
    ss << "CircleEntity[name = \"" << getName() << "\", position = "
       << getPosition() << ", radius = " << getRadius() << "]";
    return ss.str();
}
