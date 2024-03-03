#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "heap.h"

#define MAX_SIZE 1024

// Function prototypes for Dijkstra's algorithm
void dijkstra(int startX, int startY, int endX, int endY, char maze[MAX_SIZE][MAX_SIZE], int width, int height);
void reconstruct_path(int prev[MAX_SIZE * MAX_SIZE][2], int currentX, int currentY, char maze[MAX_SIZE][MAX_SIZE]);

#endif // DIJKSTRA_H
