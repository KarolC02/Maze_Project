//#include "dijsktra.h"
//#include <limits.h>
//#include <stdbool.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <assert.h>
//
//
//#define MAX_SIZE 1024
//
//// Structure to represent a cell in the maze
//typedef struct {
//    int x, y; // Coordinates of the cell
//} Cell;
//
//// Structure to represent a queue for BFS
//typedef struct {
//    Cell items[MAX_SIZE];
//    int front, rear;
//} Queue;
//
//// Function to initialize an empty queue
//void initQueue(Queue *q) {
//    q->front = q->rear = -1;
//}
//
//// Function to check if the queue is empty
//bool isEmpty(Queue *q) {
//    return q->front == -1;
//}
//
//// Function to add an item to the queue
//void enqueue(Queue *q, Cell item) {
//    assert (q->rear < MAX_SIZE-1);
//    if (q->front == -1) {
//        q->front = 0;
//    }
//    q->rear++;
//    q->items[q->rear] = item;
//}
//
//// Function to remove an item from the queue
//Cell dequeue(Queue *q) {
//
//    assert (!isEmpty(q));
//
//    Cell item = q->items[q->front];
//    if (q->front == q->rear) {
//        q->front = q->rear = -1;
//    } else {
//        q->front++;
//    }
//    return item;
//}
//
//// Function to check if a cell is valid (within bounds and not a wall)
//bool isValidCell(Maze *maze, int x, int y) {
//    return (maze->grid[y][x] != 'X'&& maze->grid[y][x] != 'P');
//}
//
//// Function to backtrack from the end cell to the start cell and mark the path cells with '*'
//void markPath(Maze *maze, int currentX, int currentY, Cell *prev) {
//
//    while (currentX != 0 && currentY != 0) {
//
//
//        maze->grid[currentY][currentX] = '*';
//        int nextX = prev[currentY * maze->width + currentX].x;
//        int nextY = prev[currentY * maze->width + currentX].y;
//        currentX = nextX;
//        currentY = nextY;
//    }
//    printf("That's it\n");
//}
//
//
//void printPrev(Cell *prev, int width, int height) {
//    printf("prev array:\n");
//    for (int y = 0; y < height; y++) {
//        for (int x = 0; x < width; x++) {
//            printf("(%d, %d) ", prev[y * width + x].x, prev[y * width + x].y);
//        }
//        printf("\n");
//    }
//
//}
//
//void BFS(Maze *maze){
//
//    Queue q;
//    initQueue(&q);
//    bool visited[maze->height][maze->width];
//    for (int i = 0; i < maze->height; i++) {
//        for (int j = 0; j < maze->width; j++) {
//            visited[i][j] = false;
//        }
//    }
//    Cell prev[maze->height][maze->width];
//
//    Cell start = {1, 0};
//
//    int currentX = 0;
//    int currentY = 0;
//
//    visited[currentY][currentX] = true;
//    enqueue(&q, start);
//
//    // Arrays to represent possible movements (up, down, left, right)
//    int dx[] = {0, 0, -1, 1};
//    int dy[] = {-1, 1, 0, 0};
//
//    while (!isEmpty(&q)) {
//        Cell current = dequeue(&q);
//
//
//        if (current.x == maze->endX && current.y == maze->endY) {
//            printPrev(prev, maze->width, maze->height);
//            markPath(maze->grid, current.x, current.y, prev);
//            printf("Path found!\n");
//            return; // Reached the destination
//        }
//
//        // Explore adjacent cells
//        for (int i = 0; i < 4; i++) {
//            int nx = current.x + dx[i];
//            int ny = current.y + dy[i];
//            if (isValidCell(maze, nx, ny) && !visited[ny][nx]) {
//                visited[ny][nx] = true;
//                enqueue(&q, (Cell){nx, ny});
//                prev[ny][nx] = current; // Store the previous cell for each cell in the path
//            }
//        }
//        printf("A jestem na (%d,%d)\n\n", current.x, current.y);
//    }
//
//    // If the end cell is unreachable
//    printf("Path not found\n");
//
//}