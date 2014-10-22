#ifndef __GROUND_HPP__
#define __GROUND_HPP__

#include "defines.hpp"
#include "entity.hpp"
#include "window.hpp"

class Ground : public BoxEntity
{
public:
    using BoxEntity::BoxEntity;

    void draw();

    static const float DEFAULT_HEIGHT;
};

#endif
