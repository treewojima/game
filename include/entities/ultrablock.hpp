#ifndef __ULTRABLOCK_HPP__
#define __ULTRABLOCK_HPP__

#include "defines.hpp"
#include "block.hpp"

class UltraBlock : public Block
{
public:
    UltraBlock(const std::string &name, const b2Vec2 position);

    void startContact(const Entity *other, const b2Fixture *otherFixture);

    std::string toString() const;

private:
    int _health;
};

#endif
