#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

#include "defines.hpp"
#include <Box2D/Box2D.h>
#include "entity.hpp"

class Block : public Entity
{
public:
    Block(const std::string &name, const b2Vec2 &position);
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
};

#endif
