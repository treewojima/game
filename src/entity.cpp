#include "defines.hpp"
#include "entity.hpp"

#include <cassert>
#include <cmath>
#include <easylogging++.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <sstream>
#include "exception.hpp"
#include "game.hpp"
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

    //LOG(DEBUG) << "created entity " << _name << "[" << position << "]";
}

Entity::~Entity()
{    
    Physics::getWorld().DestroyBody(_body);

    LOG(DEBUG) << "destroyed entity \"" << _name << "\"";
}

std::string Entity::toString() const
{
    std::ostringstream ss;
    ss << "Entity[name = \"" << getName() << "\", position = " << getPosition()
       << ", dimensions = " << getDimensions() << "]";
    return ss.str();
}

SDL_Rect Entity::getSDLRect() const
{
    auto position = Game::getCamera().worldToScreen(getPosition(), true);
    auto dimensions = Game::getCamera().worldToScreen(getDimensions());

    return SDL_Rect { static_cast<int>(std::round(position.x)),
                      static_cast<int>(std::round(position.y)),
                      static_cast<int>(std::round(dimensions.x)),
                      static_cast<int>(std::round(dimensions.y)) };
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
