#ifndef UTILS_H
#define UTILS_H

#include "heap.h"
#include "maze.h"
#include <stdbool.h>

// Structure to represent a cell in the maze
typedef struct {
    int x, y; // Coordinates of the cell
} Cell;

// Structure to represent a queue for
typedef struct {
    Cell items[MAX_SIZE];
    int front, rear;
} Queue;

// Function prototypes
void initQueue(Queue *q);
bool isEmpty(Queue *q);
void enqueue(Queue *q, Cell item);
Cell dequeueFIFO(Queue *q);
Cell dequeueLIFO(Queue *q);
bool isValidCell(Maze *maze, int nx, int ny);
void DFS(Maze *maze);
void markPath(Maze *maze);
void printPrev(Maze *maze);

#endif //UTILS_H
