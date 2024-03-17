#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "heap.h"
#include "maze.h"

#define MAX_SIZE 1024

// Function prototypes for Dijkstra's algorithm
void dijkstra(Maze *maze);
void reconstruct_path(int currentX, int currentY, Maze *maze);

#endif // DIJKSTRA_H
