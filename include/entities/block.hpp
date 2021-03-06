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

#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include "defines.hpp"
#include <Box2D/Box2D.h>
#include "entity.hpp"

class Block : public Entity
{
public:
    Block(const std::string &name, const b2Vec2 &position, int health);
    ~Block();

    void draw();

    void startContact(const Entity *other, const b2Fixture *otherFixture);

    inline b2Vec2 getPosition() const { return _body->GetPosition(); }
    inline b2Vec2 getDimensions() const { return DIMENSIONS; }

    std::string toString() const;

private:
    static const b2Vec2 DIMENSIONS;

    b2Body *_body;
    b2Fixture *_fixture;
    int _health;
    SDL_Color _color;
};

#endif
