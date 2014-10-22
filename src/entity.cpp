#include "defines.hpp"
#include "entity.hpp"

#include <cassert>
#include <cmath>
#include <easylogging++.h>
#include <SDL2/SDL.h>
#include "exception.hpp"
#include "physics.hpp"
#include "window.hpp"

Entity::Entity(const std::string &name,
               const b2Vec2 &position,
               bool dynamic) :
    _name(name),
    _body(nullptr)
{
    // Create the initial body
    b2BodyDef bodyDef;
    bodyDef.type = (dynamic ? b2_dynamicBody : b2_staticBody);
    bodyDef.position = position;
    _body = Physics::getWorld().CreateBody(&bodyDef);

    // Do the rest of the body/fixture initialization in initialize(), since
    // the default implementation uses virtual functions

    LOG(DEBUG) << "created entity " << _name << position;
}

Entity::~Entity()
{    
    Physics::getWorld().DestroyBody(_body);

    LOG(DEBUG) << "destroyed entity \"" << _name << "\"";
}

void Entity::collide(float dt, std::shared_ptr<Entity> other, SDL_Rect intersection)
{
}

SDL_Rect Entity::getSDLRect() const
{
    SDL_Rect r;
    auto position = getPosition();
    auto offset = Physics::getOriginOffset();

    r.x = (position.x + offset.x) * Physics::METERS_TO_PIXELS;
    r.y = (-position.y + offset.y) * Physics::METERS_TO_PIXELS;
    r.w = getWidth() * Physics::METERS_TO_PIXELS;
    r.h = getHeight() * Physics::METERS_TO_PIXELS;

    return r;
}

void Entity::setBody(b2Body *body)
{
    assert(body != nullptr);
    _body = body;
}

BoxEntity::BoxEntity(const std::string &name,
                     const b2Vec2 &position,
                     const b2Vec2 &dimensions,
                     bool dynamic) :
    Entity(name, position, dynamic),
    _dimensions(dimensions)
{
}

void BoxEntity::initialize()
{
    // Create the body fixture
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(getWidth() / 2, getHeight() / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;
    getBody().CreateFixture(&fixtureDef);
}

void BoxEntity::draw()
{
    auto r = getSDLRect();
    auto renderer = Window::getRenderer();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &r);
}

#if 0
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
    /*window::blit(*_texture,
                 static_cast<int>(x),
                 static_cast<int>(y));*/

    throw Exception("shouldn't be trying to draw a TexturedEntity right nao");
}
#endif
