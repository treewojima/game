#include "defines.hpp"
#include "ship.hpp"

#include "game.hpp"
#include "physics.hpp"
#include "window.hpp"

Ship::Ship(float x_, float y_, float vel_x_, float vel_y_) :
    Entity("Ship", x_, y_, vel_x_, vel_y_)
{
    static const float magnitude = 0.25f;

    _eventHandles[0] = game::registerEvent(
            SDLK_LEFT,
            [this]()
            {
                getBody().ApplyLinearImpulse(b2Vec2(-magnitude, 0),
                                             getBody().GetWorldCenter(),
                                             true);
            },
            "ShipLeftEvent");

    _eventHandles[1] = game::registerEvent(
            SDLK_RIGHT,
            [this]()
            {
                getBody().ApplyLinearImpulse(b2Vec2(magnitude, 0),
                                             getBody().GetWorldCenter(),
                                             true);
            },
            "ShipRightEvent");

    _eventHandles[2] = game::registerEvent(
            SDLK_UP,
            [this]()
            {
                getBody().ApplyLinearImpulse(b2Vec2(0, -magnitude),
                                             getBody().GetWorldCenter(),
                                             true);
            },
            "ShipUpEvent");

    _eventHandles[3] = game::registerEvent(
            SDLK_DOWN,
            [this]()
            {
                getBody().ApplyLinearImpulse(b2Vec2(0, magnitude),
                                             getBody().GetWorldCenter(),
                                             true);
            },
            "ShipDownEvent");
}

Ship::~Ship()
{
    for (int i = 0; i < 4; i++)
        game::unregisterEvent(_eventHandles[i]);
}

void Ship::initializeBody()
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(PTOM(x), PTOM(y));
    setBody(physics::getWorld().CreateBody(&bodyDef));

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(PTOM(getWidth() / 2), PTOM(getHeight() / 2));

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 1.0f;

    // Add the shape to the body.
    getBody().CreateFixture(&fixtureDef);
}

void Ship::draw()
{
    SDL_Rect r = getBoundingBox();
    //auto position = getBody().GetPosition();
    //SDL_Rect r = { position.x, position.y, getWidth(), getHeight() };
    SDL_SetRenderDrawColor(window::getRenderer(), 255, 0, 0, 0);
    SDL_RenderFillRect(window::getRenderer(), &r);
}
