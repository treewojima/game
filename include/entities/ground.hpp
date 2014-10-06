#ifndef __GROUND_HPP__
#define __GROUND_HPP__

#include "defines.hpp"
#include "entity.hpp"
#include "window.hpp"

class Ground : public Entity
{
public:
    Ground();

    void initializeBody();

    void draw();

    int getWidth() const { return window::getWidth(); }
    int getHeight() const { return HEIGHT; }

private:
    static const int HEIGHT = 20;
};

#endif
