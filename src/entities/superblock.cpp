/* game
 * Copyright (C) 2014 Scott Bishop <treewojima@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
