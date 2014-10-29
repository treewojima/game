#include "defines.hpp"
#include "entities/block.hpp"

#ifdef _ENABLE_BLOCKS

#include <SDL2/SDL.h>
#include "physics.hpp"
#include "window.hpp"

const float Block::DEFAULT_WIDTH = 80 * Physics::PIXELS_TO_METERS;
const float Block::DEFAULT_HEIGHT = 20 * Physics::PIXELS_TO_METERS;

void Block::draw()
{
    auto renderer = Window::getRenderer();

    // First, draw the filled portion of the block
    auto r = getSDLRect();
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderFillRect(renderer, &r);

    // Next, draw a set of outlines
    static const int LINE_WIDTH = 2;
    enum { TOP, BOTTOM, LEFT, RIGHT, NUM_RECTS };

    auto position = getPosition();
    int xi = static_cast<int>(position.x * Physics::METERS_TO_PIXELS);
    int yi = static_cast<int>(position.y * Physics::METERS_TO_PIXELS);
    SDL_Rect rects[NUM_RECTS];
    rects[TOP] = { xi, yi, r.w, LINE_WIDTH };
    rects[BOTTOM] = { xi, yi + r.h - LINE_WIDTH, r.w, LINE_WIDTH };
    rects[LEFT] = { xi, yi, LINE_WIDTH, r.h };
    rects[RIGHT] = { xi + r.w - LINE_WIDTH, yi, LINE_WIDTH, r.h };

    SDL_SetRenderDrawColor(renderer, 0, 0, 96, 0);
    SDL_RenderFillRects(renderer, rects, NUM_RECTS);
}

#endif
