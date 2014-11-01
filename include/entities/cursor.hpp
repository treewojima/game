#ifndef __CURSOR_HPP__
#define __CURSOR_HPP__

#include "defines.hpp"
#include "entity.hpp"

class Cursor : public Entity
{
public:
    Cursor() : Entity("Cursor") {}

    void draw();

    std::string toString() const;
};

#endif
