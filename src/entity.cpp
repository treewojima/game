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
               b2BodyType type) :
    _name(name),
    _body(nullptr)
{
    // Create the initial body
    b2BodyDef bodyDef;
    bodyDef.type = type;
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
    ss << "Entity[name = \"" << getName() << "\", position = "
       << getPosition() << "]";
    return ss.str();
}

/*SDL_Rect Entity::getSDLRect() const
{
    auto position = Game::getCamera().worldToScreen(getPosition(), true);
    auto dimensions = Game::getCamera().worldToScreen(getDimensions());

    return SDL_Rect { static_cast<int>(std::round(position.x)),
                      static_cast<int>(std::round(position.y)),
                      static_cast<int>(std::round(dimensions.x)),
                      static_cast<int>(std::round(dimensions.y)) };
}*/

void Entity::setBody(b2Body *body)
{
    assert(body != nullptr);
    _body = body;
}

BoxEntity::BoxEntity(const std::string &name,
                     const b2Vec2 &position,
                     const b2Vec2 &dimensions,
                     const SDL_Color &color,
                     bool filled,
                     b2BodyType type) :
    Entity(name, position, type),
    _color(color),
    _filled(filled),
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
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 1;
    getBody().CreateFixture(&fixtureDef);
}

void BoxEntity::draw()
{
    auto position = getPosition();
    auto dimensions = getDimensions();

    position.x -= dimensions.x / 2.f;
    position.y -= dimensions.y / 2.f;

    glColor4ub(_color.r, _color.g, _color.b, _color.a);

    if (_filled)
    {
        glRectf(position.x,
                position.y,
                position.x + dimensions.x,
                position.y + dimensions.y);
    }
    else
    {
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
    ss << "Entity[name = \"" << getName() << "\", position = " << getPosition()
       << ", dimensions = " << getDimensions() << "]";
    return ss.str();
}

CircleEntity::CircleEntity(const std::string &name,
                           const b2Vec2 &position,
                           float radius,
                           const SDL_Color &color,
                           bool filled,
                           b2BodyType type) :
    Entity(name, position, type),
    _color(color),
    _radius(radius),
    _filled(filled)
{
}

void CircleEntity::initialize()
{
    b2CircleShape shape;
    shape.m_radius = _radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 1;
    getBody().CreateFixture(&fixtureDef);
}

void CircleEntity::update(float dt)
{
    //std::cout << getPosition() << std::endl;
}

void CircleEntity::draw()
{
    auto position = getPosition();
    auto radius = getRadius();

    glColor4ub(_color.r, _color.g, _color.b, _color.a);

    glBegin(_filled ? GL_TRIANGLE_FAN : GL_LINE_LOOP);
    {
        if (_filled) glVertex2f(position.x, position.y);

        for (int angle = 0; angle <= 360; angle += 5)
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
    ss << "Entity[name = \"" << getName() << "\", position = " << getPosition()
       << ", radius = " << getRadius() << "]";
    return ss.str();
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
