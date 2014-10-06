#include "defines.hpp"
#include "entity.hpp"

#include <cassert>
#include <cmath>
#include <easylogging++.h>
#include "math.hpp"
#include "physics.hpp"
#include "window.hpp"

Entity::Entity(const std::string &name,
               float x_, float y_,
               float vel_x_, float vel_y_) :
    x(x_), y(y_),
    vel_x(vel_x_), vel_y(vel_y_),
    _name(name),
    _body(nullptr)
{
    // Do NOT call this here, since virtual/pure virtual functions in
    // base constructors causes all sorts of weirdness
    //initializeBody();

    LOG(DEBUG) << "created entity \"" << _name << "\"";
}

Entity::~Entity()
{    
    physics::getWorld().DestroyBody(_body);

    LOG(DEBUG) << "destroyed entity \"" << _name << "\"";
}

void Entity::initializeBody()
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(PTOM(x), PTOM(y));
    _body = physics::getWorld().CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(PTOM(getWidth() / 2), PTOM(getHeight() / 2));

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction and restitution.
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;

    // Add the shape to the body.
    _body->CreateFixture(&fixtureDef);
}

void Entity::update(float dt)
{
#if 0
    x += vel_x * dt;
    y += vel_y * dt;

    if (x < 0)
    {
        x = 0;
        vel_x = -vel_x;
    }
    if (x > window::getWidth() - getWidth())
    {
        x = window::getWidth() - getWidth();
        vel_x = -vel_x;
    }
    if (y < 0)
    {
        y = 0;
        vel_y = -vel_y;
    }
    if (y > window::getHeight() - getHeight())
    {
        y = window::getHeight() - getHeight();
        vel_y = -vel_y;
    }
#endif

    auto bodyPosition = getBody().GetPosition();
    auto bodyVelocity = getBody().GetLinearVelocity();

    x = MTOP(bodyPosition.x);
    y = MTOP(bodyPosition.y);
    vel_x = MTOP(bodyVelocity.x);
    vel_y = MTOP(bodyVelocity.y);
}

void Entity::collide(float dt, std::shared_ptr<Entity> other, SDL_Rect intersection)
{
    //LOG(INFO) << "collision between " << getName() << " and " << other->getName();

    //float overlap_x = x + getWidth() - other->x + other->getWidth();
    //float overlap_y = y + getHeight() - other->y + other->getHeight();
    float overlap_x = x + getWidth() - intersection.x + intersection.w;
    float overlap_y = y + getHeight() - intersection.y + intersection.h;

    if (std::abs(overlap_x) < std::abs(overlap_y))
    {
        vel_x = -vel_x;
    }
    else
    {
        vel_y = -vel_y;
    }
}

SDL_Rect Entity::getBoundingBox() const
{
    SDL_Rect r;
    r.x = static_cast<int>(x);
    r.y = static_cast<int>(y);
    r.w = getWidth();
    r.h = getHeight();

    return r;
}

TexturedEntity::TexturedEntity(const std::string &name,
                               std::shared_ptr<Texture> texture,
                               float x_, float y_,
                               float vel_x_, float vel_y_) :
    Entity(name, x_, y_, vel_x_, vel_y_),
    _texture(texture)
{
     assert(_texture.get() != nullptr);
}

void TexturedEntity::draw()
{
    window::blit(*_texture,
                 static_cast<int>(x),
                 static_cast<int>(y));
}
