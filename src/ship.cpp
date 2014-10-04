#include "defines.hpp"
#include "ship.hpp"

#include "game.hpp"
#include "window.hpp"

Ship::Ship(int x_, int y_) : Sprite("ship", x_, y_)
{
    static const int magnitude = 5;

    _eventHandles[0] = game::registerEvent(SDLK_LEFT,
                                           [this]() { this->x -= magnitude; },
                                           "ShipLeftEvent");
    _eventHandles[1] = game::registerEvent(SDLK_RIGHT,
                                           [this]() { this->x += magnitude; },
                                           "ShipRightEvent");
    _eventHandles[2] = game::registerEvent(SDLK_UP,
                                           [this]() { this->y -= magnitude; },
                                           "ShipUpEvent");
    _eventHandles[3] = game::registerEvent(SDLK_DOWN,
                                           [this]() { this->y += magnitude; },
                                           "ShipDownEvent");
}

Ship::~Ship()
{
    for (int i = 0; i < 4; i++)
        game::unregisterEvent(_eventHandles[i]);
}

void Ship::draw()
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = r.h = 20;

    SDL_SetRenderDrawColor(window::getRenderer(),
                           255, 255, 255, 0);
    SDL_RenderDrawRect(window::getRenderer(), &r);
}
