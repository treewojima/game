#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include "defines.hpp"
#include <list>
#include <memory>
#include <string>
#include "entity.hpp"

class Level
{
public:
    Level(const std::string &filename);
    ~Level();

    void update(float dt);
    void draw();
    void cullDeadEntities();

private:
    std::list<std::shared_ptr<Entity>> _entities;

    void loadFile(const std::string &filename);
};

#endif
