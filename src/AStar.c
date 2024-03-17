#include "heap.h"  
#include "maze.h" 
#include "graph_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int calculateHeuristic(int x, int y, int goalX, int goalY) {
    // Example: Manhattan distance for a grid.
    return abs(x - goalX) + abs(y - goalY);
}

void AStar(Maze *maze) {
    // Initialization similar to your Dijkstra setup, adapted for A*.
    MinHeap heap;
    initHeap(&heap, maze->height * maze->width);

    Node start = {maze->startX, maze->startY, 0, calculateHeuristic(maze->startX, maze->startY, maze->endX, maze->endY)};
    start.f = start.distance + calculateHeuristic(maze->startX, maze->startY, maze->endX, maze->endY);  // 'f' is 'g' + 'h'.
    insert(&heap, start);  // Use an adapted insert function that considers 'f'.

    while (heap.size > 0) {
        Node current = Poll(&heap);

        // Mark as visited
        maze->visited[current.y][current.x] = true;

        // Check if the goal has been reached.
        if (current.x == maze->endX && current.y == maze->endY) {
            printPrev(maze);
            markPath(maze);
            printf("Goal reached.\n");
            return;
        }

        // Explore neighbors
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};  // Right, Down, Left, Up
        for (int i = 0; i < 4; ++i) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];

            if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height && maze->grid[ny][nx] != 'X' && !maze->visited[ny][nx]) {
                int gNew = current.distance + 1;  // Assuming uniform cost to move.
                int hNew = calculateHeuristic(nx, ny, maze->endX, maze->endY);
                int fNew = gNew + hNew;
                maze->prevY[ny][nx] = current.y; // Store the previous cell for each cell in the path
                maze->prevX[ny][nx] = current.x; // Store the previous cell for each cell in the path
                // Enqueue with new costs, ensuring 'f' is considered in the heap.
                Node neighbor = {nx, ny, gNew, fNew};
                insert(&heap, neighbor);
            }
        }
    }

    // Handle failure to find a path.
    printf("Path not found.\n");
    freeHeap(&heap);  // Ensure allocated memory is freed.
}
