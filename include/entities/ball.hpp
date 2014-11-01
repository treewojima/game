#ifndef __BALL_HPP__
#define __BALL_HPP__

#include "defines.hpp"
#include <Box2D/Box2D.h>
#include "entity.hpp"

class Ball : public Entity
{
public:
    Ball(const b2Vec2 &position);
    ~Ball();

    void update(float dt);
    void draw();

    void startContact(const Entity *other, const b2Fixture *otherFixture);

    inline b2Vec2 getPosition() const { return _body->GetPosition(); }

    std::string toString() const;

private:
    static const float RADIUS;

    b2Body *_body;
    b2Fixture *_fixture;
};

#endif
