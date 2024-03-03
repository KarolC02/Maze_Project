#include "maze.h"
#include "dijsktra.h"
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <maze_file>\n", argv[0]);
        return EXIT_FAILURE;
    }


    Maze maze;
    readMazeFromFile(argv[1], &maze);

    printf("The width is %d\n", maze.width);
    printf("The height is %d\n", maze.height);
    return 1;
    dijkstra(maze.startX, maze.startY, maze.endX, maze.endY, maze.grid, maze.width, maze.height);

    return EXIT_SUCCESS;
}
