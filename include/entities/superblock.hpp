#ifndef __SUPERBLOCK_HPP__
#define __SUPERBLOCK_HPP__

#include "defines.hpp"
#include "block.hpp"

class SuperBlock : public Block
{
public:
    SuperBlock(const std::string &name, const b2Vec2 position);

    void startContact(const Entity *other, const b2Fixture *otherFixture);

    std::string toString() const;

private:
    int _health;
};

#endif
