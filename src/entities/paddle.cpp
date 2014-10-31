#include "defines.hpp"
#include "entities/paddle.hpp"

const float Paddle::DEFAULT_WIDTH = 2;
const float Paddle::DEFAULT_HEIGHT = 0.3;
const SDL_Color Paddle::DEFAULT_COLOR = { 0, 0, 0, 0 };

Paddle::Paddle(const b2Vec2 &position) :
    BoxEntity("Paddle",
              position,
              b2Vec2(DEFAULT_WIDTH, DEFAULT_HEIGHT),
              DEFAULT_COLOR)
{
    static const float magnitude = 0.75;

    _eventHandles[PADDLE_LEFT] = Game::registerEvent(
            SDLK_LEFT,
            [this](const SDL_Event &e)
            {
                //getBody().ApplyLinearImpulse(b2Vec2(-magnitude, 0),
                //                             getBody().GetWorldCenter(),
                //                             true);
                getBody().SetLinearVelocity(b2Vec2(-magnitude, 0));
            },
            "PaddleLeftEvent");

    _eventHandles[PADDLE_RIGHT] = Game::registerEvent(
            SDLK_RIGHT,
            [this](const SDL_Event &e)
            {
                //getBody().ApplyLinearImpulse(b2Vec2(magnitude, 0),
                //                             getBody().GetWorldCenter(),
                //                             true);
                getBody().SetLinearVelocity(b2Vec2(magnitude, 0));
            },
            "PaddleRightEvent");
}

Paddle::~Paddle()
{
    for (int i = 0; i < NUM_PADDLE_EVENTS; i++)
        Game::unregisterEvent(_eventHandles[i]);
}

void Paddle::initialize()
{
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(getWidth() / 2, getHeight() / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;
    getBody().CreateFixture(&fixtureDef);
}
