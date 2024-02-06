build:
	gcc -Wall -Werror -Wextra -pedantic src/*.c -I sdl/include -L sdl/lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o maze

run:
	maze.exe

clean:
	del maze.exe
