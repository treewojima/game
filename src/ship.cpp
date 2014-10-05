#include "defines.hpp"
#include "ship.hpp"

#include "game.hpp"
#include "window.hpp"

Ship::Ship(float x_, float y_, float vel_x_, float vel_y_) :
    Sprite("Ship", x_, y_, vel_x_, vel_y_)
{
    static const int magnitude = 50;

    _eventHandles[0] = game::registerEvent(SDLK_LEFT,
                                           [this]() { this->vel_x -= magnitude; },
                                           "ShipLeftEvent");
    _eventHandles[1] = game::registerEvent(SDLK_RIGHT,
                                           [this]() { this->vel_x += magnitude; },
                                           "ShipRightEvent");
    _eventHandles[2] = game::registerEvent(SDLK_UP,
                                           [this]() { this->vel_y -= magnitude; },
                                           "ShipUpEvent");
    _eventHandles[3] = game::registerEvent(SDLK_DOWN,
                                           [this]() { this->vel_y += magnitude; },
                                           "ShipDownEvent");
}

Ship::~Ship()
{
    for (int i = 0; i < 4; i++)
        game::unregisterEvent(_eventHandles[i]);
}

void Ship::draw()
{
    SDL_Rect r = getBoundingBox();
    SDL_SetRenderDrawColor(window::getRenderer(), 255, 255, 255, 0);
    SDL_RenderDrawRect(window::getRenderer(), &r);
}
