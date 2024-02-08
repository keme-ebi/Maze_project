#include "../lib/game.h"

int game_is_running = FALSE;
float time, oldTime;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;
Player player;

/**
 * inititalize_window - setups the game window
 *
 * Return: True if setup is successful else False
 */
int initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Initialization Error: %s\n", SDL_GetError());
        return FALSE;
    }

    window = SDL_CreateWindow(NULL,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIDTH,
                              HEIGHT,
                              SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window)
    {
        printf("Window Creation Error: %s\n", SDL_GetError());
        return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        return FALSE;
    }

    return TRUE;
}

/**
 * setup - sets up the player's position, direction, plane and time
 *
 * Return: void
 */
void setup(void)
{
    player.posX = 22;
    player.posY = 12;
    player.dirX = -1;
    player.dirY = 0;
    player.planeX = 0;
    player.planeY = 0.66;
    time = 0;
    oldTime = 0;
}

/**
 * process_input - checks if the exit button has been clicked
 *
 * Return: void
 */
void process_input(void)
{
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        game_is_running = FALSE;
        break;
    default:
        break;
    }
}

/**
 * render - draws objects and colors to the window
 *
 * Return: void
 */
void render(void)
{
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

/**
 * destroy_window - destroys the window once game_is_running becomes false
 *
 * Return: void
 */
void destroy_window(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}