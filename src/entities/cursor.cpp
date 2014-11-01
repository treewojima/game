#include "defines.hpp"
#include "entities/cursor.hpp"

#include <Box2D/Box2D.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "colors.hpp"
#include "game.hpp"

void Cursor::draw()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    auto position = Game::getCamera().screenToWorld(b2Vec2(x, y), true);
    const b2Vec2 DIMENSIONS(0.25, 0.25);
    position.x -= DIMENSIONS.x / 2;
    position.y -= DIMENSIONS.y / 2;

    const auto color = Colors::WHITE;
    glColor4ub(color.r, color.g, color.b, color.a);
    glRectf(position.x,
            position.y,
            position.x + DIMENSIONS.x,
            position.y + DIMENSIONS.y);
}

std::string Cursor::toString() const
{
    // This works because the words "Entity" and "Cursor" are the same length
    return Entity::toString().replace(0, 6, "Cursor");
}
