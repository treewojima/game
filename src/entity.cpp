#include "defines.hpp"
#include "entity.hpp"

#include <cmath>
#include <easylogging++.h>
#include "window.hpp"

Entity::Entity(const std::string &name,
               float x_, float y_,
               float vel_x_, float vel_y_) :
    x(x_), y(y_),
    vel_x(vel_x_), vel_y(vel_y_),
    _name(name)
{
    LOG(DEBUG) << "created entity \"" << _name << "\"";
}

Entity::~Entity()
{
    LOG(DEBUG) << "destroyed entity \"" << _name << "\"";
}

void Entity::update(float dt)
{
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
}

void Entity::collide(float dt, std::shared_ptr<Entity> other, SDL_Rect intersection)
{
    //LOG(INFO) << "collision between " << getName() << " and " << other->getName();

    float overlap_x = x + getWidth() - other->x + other->getWidth();
    float overlap_y = y + getHeight() - other->y + other->getHeight();

    if (std::abs(overlap_x) < std::abs(overlap_y))
    {
        vel_x = -vel_x;
    }
    else
    {
        vel_y = -vel_y;
    }
}
