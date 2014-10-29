#include "defines.hpp"
#include "entities/player.hpp"

#include <iostream>
#include "game.hpp"
#include "physics.hpp"
#include "window.hpp"

const float Player::WIDTH = 1;
const float Player::HEIGHT = 1;

Player::Player(const b2Vec2 &position) :
    BoxEntity("Player", position, b2Vec2(WIDTH, HEIGHT))
{
    static const float magnitude = 0.25f;

    _eventHandles[0] = Game::registerEvent(
            SDLK_LEFT,
            [this](const SDL_Event &e)
            {
                getBody().ApplyLinearImpulse(b2Vec2(-magnitude, 0),
                                             getBody().GetWorldCenter(),
                                             true);
            },
            "PlayerLeftEvent");

    _eventHandles[1] = Game::registerEvent(
            SDLK_RIGHT,
            [this](const SDL_Event &e)
            {
                getBody().ApplyLinearImpulse(b2Vec2(magnitude, 0),
                                             getBody().GetWorldCenter(),
                                             true);
            },
            "PlayerRightEvent");

    _eventHandles[2] = Game::registerEvent(
            SDLK_UP,
            [this](const SDL_Event &e)
            {
                getBody().ApplyLinearImpulse(b2Vec2(0, magnitude),
                                             getBody().GetWorldCenter(),
                                             true);
            },
            "PlayerUpEvent");

    _eventHandles[3] = Game::registerEvent(
            SDLK_DOWN,
            [this](const SDL_Event &e)
            {
                getBody().ApplyLinearImpulse(b2Vec2(0, -magnitude),
                                             getBody().GetWorldCenter(),
                                             true);
            },
            "PlayerDownEvent");
}

Player::~Player()
{
    for (int i = 0; i < 4; i++)
        Game::unregisterEvent(_eventHandles[i]);
}

void Player::initialize()
{
    // Create the body fixture
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(getWidth() / 2, getHeight() / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;
    getBody().CreateFixture(&fixtureDef);
}

void Player::draw()
{

}
