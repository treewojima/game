#include "defines.hpp"
#include "entities/block.hpp"

#include <cassert>
#include <GL/glew.h>
#include "physics.hpp"

const b2Vec2 Block::DIMENSIONS = b2Vec2(2, 0.3);

Block::Block(const std::string &name, const b2Vec2 &position) :
    Entity(name, Type::BLOCK),
    _body(nullptr),
    _fixture(nullptr)
{
    // First, create the body itself
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = b2_staticBody;
    bodyDef.userData = this;
    _body = Physics::createBody(bodyDef);

    // Now create the body fixture
    b2PolygonShape box;
    box.SetAsBox(DIMENSIONS.x / 2, DIMENSIONS.y / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.filter.categoryBits = getType();
    fixtureDef.filter.maskBits = Type::BARRIER | Type::BALL;
    _fixture = _body->CreateFixture(&fixtureDef);
}

Block::~Block()
{
    assert(_body != nullptr);
    Physics::destroyBody(_body);
}

void Block::draw()
{
    auto position = getPosition();

    // Adjust for coordinates origin
    position.x -= DIMENSIONS.x / 2.f;
    position.y -= DIMENSIONS.y / 2.f;

    // Draw a filled rectangle
    auto color = Colors::BROWN;
    glColor4ub(color.r, color.g, color.b, color.a);
    glRectf(position.x,
            position.y,
            position.x + DIMENSIONS.x,
            position.y + DIMENSIONS.y);
}

std::string Block::toString() const
{
    std::ostringstream ss;
    ss << "Block[name = \"" << getName() << "\", position = " << getPosition()
       << ", dimensions = " << getDimensions() << "]";
    return ss.str();
}
