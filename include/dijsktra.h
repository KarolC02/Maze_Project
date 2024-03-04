#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "heap.h"
#include "maze.h"

#define MAX_SIZE 1024

// Function prototypes for Dijkstra's algorithm
void dijkstra(int startX, int startY, int endX, int endY, char maze[MAX_SIZE][MAX_SIZE], int width, int height);
void dijkstra2(Maze *maze);
void reconstruct_path(int **prevX, int **prevY, int currentX, int currentY, Maze *maze);

#endif // DIJKSTRA_H
