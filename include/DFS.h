#ifndef DFS_H
#define DFS_H

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
Cell dequeue(Queue *q);
void markPath(Maze *maze, int currentX, int currentY, Cell **prev);
bool isValidCell(char maze[][MAX_SIZE], int x, int y);
void DFS(Maze *maze);
void printPrev(Cell *prev, int width, int height);

#endif //DFS_H
