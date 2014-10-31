#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "defines.hpp"
#include <Box2D/Box2D.h>
#include <easylogging++.h>
#include <SDL2/SDL.h>
#include <string>

#include "colors.hpp"

class Entity
{
public:
    Entity(const std::string &name);
    virtual ~Entity();

    virtual void update(float dt) {}
    virtual void draw() = 0;

    virtual void startContact() { std::cout << "OW -> " << toString() << std::endl; }
    virtual void endContact() { std::cout << "phew -> " << toString() << std::endl; }

    inline std::string getName() const { return _name; }

    virtual std::string toString() const;

private:
    std::string _name;
};

class BoxEntity : public Entity
{
public:
    BoxEntity(const std::string &name,
              const b2Vec2 &position,
              const b2Vec2 &dimensions,
              const SDL_Color &color = Colors::BLACK,
              bool filled = true);
    ~BoxEntity();

    void draw();

    virtual inline b2Vec2 getPosition() const { return _body->GetPosition(); }
    virtual inline b2Vec2 getDimensions() const { return _dimensions; }

    std::string toString() const;

protected:
    inline b2Body &getBody() { return *_body; }

private:
    b2Body *_body;
    const b2Vec2 _dimensions;
    SDL_Color _color;
    bool _filled;
};

class CircleEntity : public Entity
{
public:
    CircleEntity(const std::string &name,
                 const b2Vec2 &position,
                 float radius,
                 const SDL_Color &color = Colors::BLACK,
                 bool filled = true);
    ~CircleEntity();

    void draw();

    virtual inline b2Vec2 getPosition() const { return _body->GetPosition(); }
    virtual inline float getRadius() const { return _radius; }

    std::string toString() const;

protected:
    inline b2Body &getBody() { return *_body; }

private:
    b2Body *_body;
    const float _radius;
    SDL_Color _color;
    bool _filled;
};

// Helper stream operators
template <class T>
inline std::ostream &operator<<(std::ostream &stream, const Entity &e)
{
    stream << e.toString();
    return stream;
}

inline MAKE_LOGGABLE(Entity, e, stream)
{
    stream << e.toString();
    return stream;
}

#endif
