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
    printMaze(&maze);
    //dijkstra2(&maze);
    //randomPath(&maze);
//    BFS(&maze);
    DFS(&maze);

    printMaze(&maze);
    return EXIT_SUCCESS;
}
