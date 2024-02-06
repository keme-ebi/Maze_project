#include "../lib/game.h"

int main(int argc, char *argv[])
{
    game_is_running = initialize_window();

    setup();
    while (game_is_running)
    {
        process_input();
        render();
    }

    destroy_window();

    return (0);
}