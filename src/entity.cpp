#include "defines.hpp"
#include "entity.hpp"

#include <cassert>
#include <cmath>
#include <easylogging++.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <sstream>
#include "physics.hpp"

Entity::Entity(const std::string &name, Type type) :
    _name(name),
    _type(type),
    _markedForDeath(false)
{
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
