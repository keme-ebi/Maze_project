#include "../lib/game.h"

/**
 * main - runs the program
 *
 * @argc: number of arguments, though not used but essential for this program
 * @argv: strings of arguments, same as argc
 *
 * Return: always 0.
 */
int main(int argc, char *argv[])
{
    game_is_running = initialize_window();

    setup();
    while (game_is_running)
    {
        process_input();
        ray();
        // render();
    }

    destroy_window();

    return (0);
}