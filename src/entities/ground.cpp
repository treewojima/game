#include "defines.hpp"
#include "ground.hpp"
#include "physics.hpp"

Ground::Ground() : Entity("Ground")
{
    y = PTOM(window::getHeight() - getHeight());
}

void Ground::initializeBody()
{
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(PTOM(x), PTOM(y));

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    setBody(physics::getWorld().CreateBody(&groundBodyDef));

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(PTOM(window::getWidth()), PTOM(getHeight() / 2));

    // Add the ground fixture to the ground body.
    getBody().CreateFixture(&groundBox, 0.0f);
}

void Ground::draw()
{
    SDL_Rect r = getBoundingBox();
    //auto position = getBody().GetPosition();
    //SDL_Rect r = { position.x, position.y, getWidth(), getHeight() };
    SDL_SetRenderDrawColor(window::getRenderer(), 128, 128, 128, 0);
    SDL_RenderFillRect(window::getRenderer(), &r);
}
