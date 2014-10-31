#include "defines.hpp"
#include "entities/ball.hpp"

#include <cassert>
#include <GL/glew.h>
#include "colors.hpp"
#include "physics.hpp"

const float Ball::RADIUS = 0.15;

Ball::Ball(const b2Vec2 &position) :
    Entity("Ball"),
    _body(nullptr),
    _fixture(nullptr)
{
    // First, create the body itself
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = this;
    _body = Physics::createBody(bodyDef);

    // Now create the body fixture
    b2CircleShape shape;
    shape.m_radius = RADIUS;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0;
    fixtureDef.restitution = 1;
    _fixture = _body->CreateFixture(&fixtureDef);

    // Set it moving!
    _body->ApplyLinearImpulse(b2Vec2(0.5, 0.5), position, true);
}

Ball::~Ball()
{
    assert(_body != nullptr);
    Physics::destroyBody(_body);
}

void Ball::update(float dt)
{
    // If we're going too fast, slooooooow down
    const float MAX_SPEED = 8;
    static bool wat = false;

    auto speed = _body->GetLinearVelocity().Length();
    if (speed > MAX_SPEED)
    {
        wat = true;
        std::cout << "slooooow down" << std::endl;
        _body->SetLinearDamping(0.5);
    }
    else if (speed < MAX_SPEED)
    {
        if (wat)
        {
            std::cout << "okay good" << std::endl;
            wat = false;
        }
        _body->SetLinearDamping(0);
    }
}

void Ball::draw()
{
    auto position = getPosition();

    auto color = Colors::RED;
    glColor4ub(color.r, color.g, color.b, color.a);

    glBegin(GL_TRIANGLE_FAN);
    {
        // Set the center vertex
        glVertex2f(position.x, position.y);

        // Adjust the stepping for more/less precision (should be a factor
        // of 360)
        const int STEP = 20;
        for (int angle = 0; angle <= 360; angle += STEP)
        {
            glVertex2f(position.x + std::sin(angle * (M_PI / 180)) * RADIUS,
                       position.y + std::cos(angle * (M_PI / 180)) * RADIUS);
        }
    }
    glEnd();
}

std::string Ball::toString() const
{
    std::ostringstream ss;
    ss << "Ball[name = \"" << getName() << "\", position = "
       << getPosition() << ", radius = " << RADIUS << "]";
    return ss.str();
}
