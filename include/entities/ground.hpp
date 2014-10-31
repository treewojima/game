#ifndef __GROUND_HPP__
#define __GROUND_HPP__

#include "defines.hpp"
#include "entity.hpp"

#ifdef _ENABLE_GROUND

class Ground : public BoxEntity
{
public:
    using BoxEntity::BoxEntity;

    static const float DEFAULT_HEIGHT;
};

#endif

#endif
