#include "maze.h"
#include "dijsktra.h"
#include "DFS.h"
#include <stdio.h>

int main(int argc, char **argv) {
    printf("HELLO\n");
    if (argc != 2) {
        printf("Usage: %s <maze_file>\n", argv[0]);
        return EXIT_FAILURE;
    }


    Maze maze;

    readMazeFromFile(argv[1], &maze);
    // printMaze(&maze);
    // dijkstra(&maze);
    // randomPath(&maze);
    // BFS(&maze);
    printf("NO SIEMA\n");
    DFS(&maze);

    printMaze(&maze);
    return EXIT_SUCCESS;
}
