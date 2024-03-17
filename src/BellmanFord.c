#include "maze.h"
#include "graph_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void bellmanFord(Maze *maze) {
    // Initialize distances
    int **distances = (int**)malloc(maze->height * sizeof(int*));
    if (distances == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < maze->height; ++i) {
        distances[i] = (int*)malloc(maze->width * sizeof(int));
        if (distances[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < maze->width; j++) {
            distances[i][j] = INT_MAX; // Initialize all distances as infinite
        }
    }

    distances[maze->startY][maze->startX] = 0; // Distance to start node is 0

    // Bellman-Ford algorithm iteration
    for (int vertex = 0; vertex < maze->height * maze->width - 1; vertex++) {
        for (int y = 0; y < maze->height; y++) {
            for (int x = 0; x < maze->width; x++) {
                if (distances[y][x] == INT_MAX) continue; // Skip unreachable nodes
                
                int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Directions: Right, Down, Left, Up
                for (int i = 0; i < 4; ++i) {
                    int nx = x + directions[i][0];
                    int ny = y + directions[i][1];

                    if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height && maze->grid[ny][nx] != 'X') {
                        int newDist = distances[y][x] + 1; // Assuming cost of 1 for each move
                        if (newDist < distances[ny][nx]) {
                            distances[ny][nx] = newDist;
                            maze->prevX[ny][nx] = x;
                            maze->prevY[ny][nx] = y;
                        }
                    }
                }
            }
        }
    }


    markPath(maze); 

    // Free allocated memory
    for (int i = 0; i < maze->height; ++i) {
        free(distances[i]);
    }
    free(distances);
}
