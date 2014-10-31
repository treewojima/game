#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include "defines.hpp"
#include "entity.hpp"

#ifdef _ENABLE_BLOCKS

class Block : public BoxEntity
{
public:
    using BoxEntity::BoxEntity;

    static const float DEFAULT_WIDTH;
    static const float DEFAULT_HEIGHT;
};

#endif

#endif
