#include "../lib/game.h"

/**
 * ray - implements everything needed for raycasting
 *
 * Return: void
 */
void ray(void)
{
    int x;

    for (x = 0; x < WIDTH; x++)
    {
        float cameraX = 2 * x / (float)WIDTH - 1; /* x- coordinate on the camera plane */
        /* directions of the ray */
        float rayDirX = -1 + cameraX;
        float rayDirY = 0;
        /* mapX and Y represents square of the map the ray is currently */
        int mapX = (int)player.posX;
        int mapY = (int)player.posY;
        /* sideDistX and Y are the distance the ray has to travel from start to first x or y-side */
        float sideDistX = 0;
        float sideDistY = 0;
        /* deltaDistX and Y are the distance the ray has to go from one x or y-side to the next */
        float deltaDistX = (rayDirX == 0) ? 1e30f : fabsf(1 / rayDirX);
        float deltaDistY = (rayDirY == 0) ? 1e30f : fabsf(1 / rayDirY);
        /* stepX and Y are direction to step in x or y-direction */
        int stepX, stepY;
        /**
         * hit - checks if there was a wall
         * side - checks if a NS or EW wall was hit
         */
        int side, hit = 0;
    }
}