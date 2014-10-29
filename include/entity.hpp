#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "defines.hpp"
#include <Box2D/Box2D.h>
#include <easylogging++.h>
#include <memory>
#include <SDL2/SDL.h>
#include <string>

#include "physics.hpp"
#include "texture.hpp"

class Entity
{
public:
    Entity(const std::string &name, const b2Vec2 &position, bool dynamic = true);
    virtual ~Entity();

    virtual void initialize() = 0;
    virtual void update(float dt) {}
    virtual void draw() = 0;

    inline std::string getName() const { return _name; }
    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;
    inline b2Body &getBody() const { return *_body; }
    inline const b2Vec2 &getPosition() const { return getBody().GetPosition(); }
    inline const b2Vec2 getDimensions() const { return b2Vec2(getWidth(), getHeight()); }

    virtual std::string toString() const;

protected:
    SDL_Rect getSDLRect() const;
    void setBody(b2Body *body);

private:
    std::string _name;
    b2Body *_body;
};

class BoxEntity : public Entity
{
public:
    BoxEntity(const std::string &name,
              const b2Vec2 &position,
              const b2Vec2 &dimensions,
              bool dynamic = true);

    void initialize();

    inline float getWidth() const { return _dimensions.x; }
    inline float getHeight() const { return _dimensions.y; }

private:
    // This assumes that the Box2D box fixture dimensions never change
    const b2Vec2 _dimensions;
};

#if 0
class TexturedEntity : public BoxEntity
{
public:
    TexturedEntity(const std::string &name,
                   std::shared_ptr<Texture> texture);

    void draw();

    float getWidth() const
        { return getTexture()->getWidth() * physics::PIXELS_TO_METERS; }
    float getHeight() const
        { return getTexture()->getHeight() * physics::PIXELS_TO_METERS; }

    inline std::shared_ptr<Texture> getTexture() const { return _texture; }

private:
    std::shared_ptr<Texture> _texture;
};
#endif

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
