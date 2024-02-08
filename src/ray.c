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
        float rayDirX = -1 + cameraX;             /* x direction of ray */
        float rayDirY = 0;                        /* y direction of ray */
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

        calc_steps(rayDirX, rayDirY, &stepX, &stepY, &sideDistX, &sideDistY, player.posX, player.posY, mapX, mapY, deltaDistX, deltaDistY);

        performDDA(&mapX, &mapY, &sideDistX, &sideDistY, &deltaDistX, &deltaDistY, &rayDirX, &rayDirY, &stepX, &stepY, &hit, &side);

        float perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);
        int lineHeight = (int)(HEIGHT / perpWallDist);

        int drawStart, drawEnd;
        calculateDrawLimits(&drawStart, &drawEnd, lineHeight);

        int r, g, b;
        color(mapX, mapY, &r, &g, &b);

        if (side == 1)
        {
            r /= 2;
            g /= 2;
            b /= 2;
        }

        drawLine(x, drawStart, drawEnd, r, g, b);
    }
    render();
}

/**
 * calc_steps - calculates steps and initialize sideDistX and Y
 * @rayDirX: direction of ray on x axis
 * @rayDirY: direction of ray on y axis
 * @stepX: pointer to step in x-direction
 * @stepY: pointer to step in y-direction
 * @sideDistX: pointer to x-side ray travel distance
 * @sideDistY: pointer to y-side ray travel distance
 * @posX: player's position on x axis
 * @posY: player's position on y axis
 * @mapX: square of map on x
 * @mapY: square of map on y
 * @deltaDistX: ray distance from one x to the other
 * @deltaDistY: ray distance from on y to the other
 *
 * Return: None
 */
void calc_steps(float rayDirX, float rayDirY, int *stepX, int *stepY, float *sideDistX, float *sideDistY, float posX, float posY, int mapX, int mapY, float deltaDistX, float deltaDistY)
{
    if (rayDirX < 0)
    {
        *stepX = -1;
        *sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
        *stepX = 1;
        *sideDistX = (mapX + 1.0f - posX) * deltaDistX;
    }

    if (rayDirY < 0)
    {
        *stepY = -1;
        *sideDistY = (posY - mapX) * deltaDistY;
    }
    else
    {
        *stepY = 1;
        *sideDistY = (mapY + 1.0f - posY) * deltaDistY;
    }
}

/**
 * performDDA - performs digital differential analysis
 *
 * @mapX: square of map on x
 * @mapY: square of map on y
 * @sideDistX: x-side ray travel distance
 * @sideDistY: y-side ray travel distance
 * @deltaDistX: ray distance from one x to the other
 * @deltaDistY: ray distance form one y to the other
 * @rayDirX: ray direction on x axis
 * @rayDirY: ray direction on y axis
 * @stepX: step in x-direction
 * @stepY: step in y-direction
 * @hit: wall hit check
 * @side: NS or EW wll hit check
 *
 * Return: None
 */
void performDDA(int *mapX, int *mapY, float *sideDistX, float *sideDistY, float *deltaDistX, float *deltaDistY, float *rayDirX, float *rayDirY, int *stepX, int *stepY, int *hit, int *side)
{
    while (*hit == 0)
    {
        if (*sideDistX < *sideDistY)
        {
            *sideDistX += *deltaDistX;
            *mapX += *stepX;
            *side = 0;
        }
        else
        {
            *sideDistY += *deltaDistY;
            *mapY += *stepY;
            *side = 1;
        }

        if (map[*mapX][*mapY] > 0)
        {
            *hit = 1;
        }
    }
}

/**
 * calculateDrawLimits -calculates the lowest and highest pixel to fill in current stripe
 *
 * @drawStart: start of draw line
 * @drawEnd: end of draw line
 * @lineHeight: height of line to draw on screen
 */
void calculateDrawLimits(int *drawStart, int *drawEnd, int lineHeight)
{
    *drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (*drawStart < 0)
    {
        *drawStart = 0;
    }
    *drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (*drawEnd >= HEIGHT)
    {
        *drawEnd = HEIGHT - 1;
    }
}

/**
 * color - create color for different walls
 *
 * @mapX: square of map at x
 * @mapY: square of map at y
 * @r: value for red color
 * @g: value for green color
 * @b: value for blue color
 */
void color(int mapX, int mapY, int *r, int *g, int *b)
{
    switch (map[mapX][mapY])
    {
    case 1:
        *r = 255;
        *g = 0;
        *b = 201;
        break;
    case 2:
        *r = 0;
        *g = 255;
        *b = 0;
    default:
        *r = 255;
        *g = 255;
        *b = 0;
        break;
    }
}