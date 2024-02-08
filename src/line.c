#include "../lib/game.h"

/**
 * drawLine - draws the wall color
 *
 * @x: x
 * @startY: drawStart
 * @endY: drawEnd
 * @r: value for red color
 * @g: value for green color
 * @b: value for blue color
 */
void drawLine(int x, int startY, int endY, int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    for (int y = startY; y <= endY; y++)
    {
        SDL_RenderDrawPoint(renderer, x, y);
    }
}