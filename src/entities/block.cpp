#include "defines.hpp"
#include "block.hpp"

#include <SDL2/SDL.h>
#include "window.hpp"

void Block::draw()
{
    SDL_Rect r = getBoundingBox();

    // First, draw the filled portion of the block
    SDL_SetRenderDrawColor(window::getRenderer(), 0, 0, 255, 0);
    SDL_RenderFillRect(window::getRenderer(), &r);

    // Next, draw a set of outlines
    static const int LINE_WIDTH = 2;
    enum { TOP, BOTTOM, LEFT, RIGHT, NUM_RECTS };

    int xi = static_cast<int>(x);
    int yi = static_cast<int>(y);
    SDL_Rect rects[NUM_RECTS];
    rects[TOP] = { xi, yi, r.w, LINE_WIDTH };
    rects[BOTTOM] = { xi, yi + r.h - LINE_WIDTH, r.w, LINE_WIDTH };
    rects[LEFT] = { xi, yi, LINE_WIDTH, r.h };
    rects[RIGHT] = { xi + r.w - LINE_WIDTH, yi, LINE_WIDTH, r.h };

    SDL_SetRenderDrawColor(window::getRenderer(), 0, 0, 96, 0);
    SDL_RenderFillRects(window::getRenderer(), rects, NUM_RECTS);
}

