#ifndef __PADDLE_HPP__
#define __PADDLE_HPP__

#include "defines.hpp"
#include "entity.hpp"
#include "game.hpp"

class Walls;

class Paddle : public Entity
{
public:
    Paddle(const b2Vec2 &position, std::shared_ptr<Walls> walls);
    ~Paddle();

    void draw();

    inline b2Vec2 getPosition() const { return _body->GetPosition(); }
    inline b2Vec2 getDimensions() const { return DIMENSIONS; }

    std::string toString() const;

private:
    static const b2Vec2 DIMENSIONS;
    enum { PADDLE_LEFT, PADDLE_RIGHT, NUM_PADDLE_EVENTS };

    b2Body *_body;
    b2Fixture *_fixture;
    Game::Event::Handle _eventHandles[NUM_PADDLE_EVENTS];

    void registerEvents();
};

#endif
