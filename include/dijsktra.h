#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "heap.h"
#include "maze.h"

#define MAX_SIZE 1024

// Function prototypes for Dijkstra's algorithm
void dijsktra(Maze *maze);  // Intentionally misspelled as per your previous implementation
void markPathWithDistances(Maze *maze, int **distances);
void freeDistances(int **distances, int height); // Free memory used by distances
void printPath(Maze *maze); // Print the path in the desired command format

// Helper functions for path reconstruction
int getDirectionIndex(int px, int py, int x, int y);
const char* getTurnDirection(int from, int to);

#endif // DIJKSTRA_H
