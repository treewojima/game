#include "defines.hpp"
#include "level.hpp"

#include <boost/tokenizer.hpp>
#include <Box2D/Box2D.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "entities/block.hpp"
#include "entities/superblock.hpp"
#include "entities/ultrablock.hpp"
#include "exception.hpp"
#include "game.hpp"

Level::Level(const std::string &filename)
{
    loadFile(filename);
}

Level::~Level()
{
    _entities.clear();
}

void Level::update(float dt)
{
    for (auto entity : _entities)
    {
        entity->update(dt);
    }
}

void Level::draw()
{
    for (auto entity : _entities)
    {
        entity->draw();
    }
}

void Level::cullDeadEntities()
{
    _entities.remove_if([](std::shared_ptr<Entity> e)
    {
        return e->isMarkedForDeath();
    });
}

void Level::loadFile(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::ostringstream ss;
        ss << "Could not open level file: " << filename;
        throw Exception(ss.str());
    }

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    for (const auto &line : lines)
    {
        boost::tokenizer<boost::escaped_list_separator<char>> tokens(line);
        auto iter = tokens.begin();

        auto name = *iter++;
        auto row = std::stof(*iter++);
        auto col = std::stof(*iter++);

        const auto camera = Game::getCamera();
        b2Vec2 position(camera.getWorldWidth() / 8 * col,
                        camera.getWorldHeight() - (camera.getWorldHeight() / 16 * row));

        Block *blockPtr;
        if (col == 2 || col == 6)
        {
            blockPtr = new SuperBlock(name, position);
        }
        else if (col == 4)
        {
            blockPtr = new UltraBlock(name, position);
        }
        else
        {
            blockPtr = new Block(name, position);
        }
        _entities.push_back(std::shared_ptr<Block>(blockPtr));
    }
}
