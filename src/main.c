#include "maze.h"
#include "dijsktra.h"
#include "RightHandRule.h"
#include "DFS.h"
#include "BFS.h"
#include "BellmanFord.h"
#include "AStar.h"
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
    dijsktra(&maze);
    // randomPath(&maze);
    // BFS(&maze);
    // DFS(&maze);
    // AStar(&maze);
    // rightHandRule(&maze);
    // bellmanFord(&maze);

    // printMaze(&maze);
    return EXIT_SUCCESS;
}
