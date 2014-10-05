#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "defines.hpp"
#include <memory>
#include <SDL2/SDL.h>
#include <string>

class Entity
{
public:
    Entity(const std::string &name,
           float x_ = 0, float y_ = 0,
           float vel_x_ = 0, float vel_y_ = 0);
    virtual ~Entity();

    virtual void update(float dt);
    virtual void collide(float dt, std::shared_ptr<Entity> other, SDL_Rect intersection);

    inline std::string getName() const { return _name; }
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    inline SDL_Rect getBoundingBox() const
    {
        SDL_Rect r;
        r.x = static_cast<int>(x);
        r.y = static_cast<int>(y);
        r.w = getWidth();
        r.h = getHeight();

        return r;
    }

    float x, y;
    float vel_x, vel_y;

private:
    std::string _name;
};

#endif
