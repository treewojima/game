#include "defines.hpp"
#include "entities/walls.hpp"

#include "game.hpp"
#include "physics.hpp"

Walls::Walls() :
    Entity("Walls"),
    _body(nullptr),
    _bottomFixture(nullptr)
{
    b2BodyDef bodyDef;
    bodyDef.position.SetZero();
    bodyDef.type = b2_staticBody;
    bodyDef.userData = this;
    _body = Physics::createBody(bodyDef);

    b2EdgeShape edge;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &edge;

    const float WORLD_WIDTH = Game::getCamera().getWorldWidth();
    const float WORLD_HEIGHT = Game::getCamera().getWorldHeight();

    // Bottom wall/fixture
    edge.Set(b2Vec2_zero, b2Vec2(WORLD_WIDTH, 0));
    _bottomFixture = _body->CreateFixture(&fixtureDef);

    // Other walls
    edge.Set(b2Vec2_zero, b2Vec2(0, WORLD_HEIGHT));
    _body->CreateFixture(&fixtureDef);
    edge.Set(b2Vec2(0, WORLD_HEIGHT),
            b2Vec2(WORLD_WIDTH, WORLD_HEIGHT));
    _body->CreateFixture(&fixtureDef);
    edge.Set(b2Vec2(WORLD_WIDTH, WORLD_HEIGHT),
            b2Vec2(WORLD_WIDTH, 0));
    _body->CreateFixture(&fixtureDef);
}

Walls::~Walls()
{
    assert(_body != nullptr);
    Physics::destroyBody(_body);
}
