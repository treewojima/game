#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include "defines.hpp"
#include <easylogging++.h>
#include <string>

class Entity
{
public:
    Entity(const std::string &name) : _name(name)
    {
        LOG(DEBUG) << "created entity \"" << _name << "\"";
    }

    virtual ~Entity()
    {
        LOG(DEBUG) << "destroyed entity \"" << _name << "\"";
    }

    virtual void update() {}

    inline std::string getName() const { return _name; }

private:
    std::string _name;
};

#endif
