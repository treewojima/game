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
