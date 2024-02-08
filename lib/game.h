#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define WIDTH 640
#define HEIGHT 480
#define mapHeight 18
#define mapWidth 18

/**
 * struct Player - a player struct
 *
 * @posX: position of the player on the x axis
 * @posY: position of the player on the y axis
 * @dirX: direction of the player on the x axis
 * @dirY: direction of the player on the y axis
 * @planeX: camera plane of the player on the x axis
 * @planeY: camera plane of the player on the y axis
 */
typedef struct Player
{
    float posX;
    float posY;
    float dirX;
    float dirY;
    float planeX;
    float planeY;
} Player;

extern Player player;
extern float time;
extern float oldTime;
extern int map[mapWidth][mapHeight];
extern int game_is_running;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;

int initialize_window(void);
void setup(void);
void process_input(void);
void render(void);
void update(void);
void destroy_window(void);
void ray(void);
void calc_steps(float rayDirX, float rayDirY, int *stepX, int *stepY, float *sideDistX, float *sideDistY, float posX, float posY, int mapX, int mapY, float deltaDistX, float deltaDistY);
void performDDA(int *mapX, int *mapY, float *sideDistX, float *sideDistY, float *deltaDistX, float *deltaDistY, float *rayDirX, float *rayDirY, int *stepX, int *stepY, int *hit, int *side);
void drawLine(int x, int startY, int endY, int r, int g, int b);
void color(int mapX, int mapY, int *r, int *g, int *b);

#endif /* GAME_H */