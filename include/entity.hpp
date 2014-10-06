#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "defines.hpp"
#include <cassert>
#include <Box2D/Box2D.h>
#include <memory>
#include <SDL2/SDL.h>
#include <string>
#include "texture.hpp"

class Entity
{
public:
    Entity(const std::string &name,
           float x_ = 0, float y_ = 0,
           float vel_x_ = 0, float vel_y_ = 0);
    virtual ~Entity();

    virtual void initializeBody();

    virtual void update(float dt);
    virtual void draw() = 0;
    virtual void collide(float dt, std::shared_ptr<Entity> other, SDL_Rect intersection);

    inline std::string getName() const { return _name; }
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    SDL_Rect getBoundingBox() const;
    b2Body &getBody() const { return *_body; }

    float x, y;
    float vel_x, vel_y;

protected:
    void setBody(b2Body *body)
    {
        assert(body != nullptr);
        _body = body;
    }

private:
    std::string _name;
    b2Body *_body;
};

class TexturedEntity : public Entity
{
public:
    TexturedEntity(const std::string &name,
                   std::shared_ptr<Texture> texture,
                   float x_ = 0, float y_ = 0,
                   float vel_x_ = 0, float vel_y_ = 0);

    void draw();

    int getWidth() const { return getTexture()->getWidth(); }
    int getHeight() const { return getTexture()->getHeight(); }

    inline std::shared_ptr<Texture> getTexture() const { return _texture; }

private:
    std::shared_ptr<Texture> _texture;
};

#endif
