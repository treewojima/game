#include "defines.hpp"
#include "entities/superblock.hpp"
#include "physics.hpp"

namespace
{
    const int NUM_HEALTH = 2;

    const SDL_Color COLORS[] = { Colors::BLUE,
                                 Colors::RED };
}

SuperBlock::SuperBlock(const std::string &name, const b2Vec2 position) :
    Block(name, position),
    _health(NUM_HEALTH)
{
    _color = COLORS[NUM_HEALTH - 1];
}

void SuperBlock::startContact(const Entity *other, const b2Fixture *otherFixture)
{
    assert(_health >= 0 && _health <= NUM_HEALTH);

    if (other->getName() == "Ball")
    {
        _health--;
        _color = COLORS[_health - 1];
    }

    if (!_health)
    {
        markForDeath();
    }
}

std::string SuperBlock::toString() const
{
    std::ostringstream ss;
    ss << "SuperBlock[name = \"" << getName() << "\", position = " << getPosition()
       << ", dimensions = " << getDimensions() << ", health = " << _health << "]";
    return ss.str();
}
