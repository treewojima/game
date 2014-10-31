#include "defines.hpp"
#include "entities/paddle.hpp"

#include <cassert>
#include <GL/glew.h>
#include "entities/walls.hpp"
#include "physics.hpp"

const b2Vec2 Paddle::DIMENSIONS = b2Vec2(2, 0.3);

Paddle::Paddle(const b2Vec2 &position, std::shared_ptr<Walls> walls) :
    Entity("Paddle"),
    _body(nullptr),
    _fixture(nullptr)
{
    // First, create the body itself
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.linearDamping = 0.7;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = this;
    _body = Physics::createBody(bodyDef);

    // Now create the body fixture
    b2PolygonShape box;
    box.SetAsBox(DIMENSIONS.x / 2, DIMENSIONS.y / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 0.1;
    _fixture = _body->CreateFixture(&fixtureDef);

    // Set up a prismatic joint to restrict movement
    b2PrismaticJointDef jointDef;
    jointDef.Initialize(_body, walls->_body, position, b2Vec2(1, 0));
    jointDef.collideConnected = true;
    Physics::getWorld().CreateJoint(&jointDef);

    // Finally, set up keyboard control events
    registerEvents();
}

Paddle::~Paddle()
{
    assert(_body != nullptr);
    Physics::destroyBody(_body);

    for (int i = 0; i < NUM_PADDLE_EVENTS; i++)
        Game::unregisterEvent(_eventHandles[i]);
}

void Paddle::draw()
{
    auto position = getPosition();

    // Adjust for coordinates origin
    position.x -= DIMENSIONS.x / 2.f;
    position.y -= DIMENSIONS.y / 2.f;

    // Draw a filled rectangle
    auto color = Colors::GRAY;
    glColor4ub(color.r, color.g, color.b, color.a);
    glRectf(position.x,
            position.y,
            position.x + DIMENSIONS.x,
            position.y + DIMENSIONS.y);
}

std::string Paddle::toString() const
{
    std::ostringstream ss;
    ss << "Paddle[name = \"" << getName() << "\", position = " << getPosition()
       << ", dimensions = " << getDimensions() << "]";
    return ss.str();
}

void Paddle::registerEvents()
{
    static const float magnitude = 0.25;

    _eventHandles[PADDLE_LEFT] = Game::registerEvent(
            SDL_SCANCODE_LEFT,
            [this](const SDL_Event &e)
            {
                _body->ApplyLinearImpulse(b2Vec2(-magnitude, 0),
                                          _body->GetWorldCenter(),
                                          true);
            },
            "PaddleLeftEvent");

    _eventHandles[PADDLE_RIGHT] = Game::registerEvent(
            SDL_SCANCODE_RIGHT,
            [this](const SDL_Event &e)
            {
                _body->ApplyLinearImpulse(b2Vec2(magnitude, 0),
                                          _body->GetWorldCenter(),
                                          true);
            },
            "PaddleRightEvent");
}
