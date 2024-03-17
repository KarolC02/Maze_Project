#include "dijsktra.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#define MAX_SIZE 1024

// Structure to represent a cell in the maze
typedef struct {
    int x, y; // Coordinates of the cell
} Cell;

typedef struct CellNode {
    Cell cell;          // The cell data
    struct CellNode* next; // Pointer to the next node in the list
    struct CellNode* prev; // Pointer to the next node in the list
} CellNode;


// Structure to represent a queue for BFS
typedef struct {
    CellNode* head; // Pointer to the first node in the list
    CellNode* tail; // Pointer to the last node in the list
} Queue;


// Function to initialize an empty queue
void initQueue(Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

// Function to check if the queue is empty
bool isEmpty(Queue* queue) {
    return queue->head == NULL;
}

bool isValidCell(Maze *maze, int nx, int ny) {
    return nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height && maze->grid[ny][nx] != 'X' && !maze->visited[ny][nx];
}

// Function to add an item to the queue
void enqueue(Queue* queue, Cell cell) {
    CellNode* newNode = (CellNode*)malloc(sizeof(CellNode));
    if (newNode == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }
    newNode->cell = cell; // Set the cell data
    newNode->next = NULL; // The new node will be the last node, so next is NULL
    newNode->prev = NULL; // The new node will be the last node, so next is NULL

    if (queue->tail != NULL) {
        newNode->prev = queue->tail;
        queue->tail->next = newNode; // Link the new node
    }
    queue->tail = newNode; // Update the tail to the new node

    if (queue->head == NULL) {
        queue->head = newNode; // If the list was empty, head is also the new node
    }
}



// Function to remove an item from the queue
Cell dequeueFIFO(Queue* queue) {
    if (isEmpty(queue) ) {
        // Handle the case when the queue is empty
        exit(EXIT_FAILURE); // Or return a special Cell value indicating an error
    }

    CellNode* tempNode = queue->head;
    Cell cell = tempNode->cell; // Retrieve the cell to return

    queue->head = queue->head->next; // Move the head to the next node
    if (queue->head == NULL) {
        queue->tail = NULL; // If the list becomes empty, update tail as well
    }

    free(tempNode); // Free the dequeued node
    return cell; // Return the dequeued cell
}


Cell dequeueLIFO(Queue* queue) {
    if (isEmpty(queue) ) {
        // Handle the case when the queue is empty
        exit(EXIT_FAILURE); // Or return a special Cell value indicating an error
    }

    CellNode* tempNode = queue->tail;
    Cell cell = tempNode->cell; // Retrieve the cell to return

    queue->tail = queue->tail->prev; // Move the head to the next node
    if (queue->tail == NULL) {
        queue->head = NULL; // If the list becomes empty, update tail as well
    }

    free(tempNode); // Free the dequeued node
    return cell; // Return the dequeued cell
}


// Function to backtrack from the end cell to the start cell and mark the path cells with '*'


void printPrev(Maze *maze) {
    printf("prev array:\n");
    for (int y = 0; y < maze->height; y++) {
        for (int x = 0; x < maze->width; x++) {
            printf("(%d, %d) ", maze->prevY[y][x], maze->prevX[y][x]);
        }
        printf("\n");
    }
}

void markPath( Maze *maze ){
    if ( maze->prevX[maze->endY][maze->endX] == -1 || maze->prevY[maze->endY][maze->endX] == -1 ){
        printf("Path was not found\n");
        return;
    }
    int currentX = maze->endX;
    int currentY = maze->endY;
    int tempX;
    int tempY;
    while( currentX != -1 && currentY != -1 ){
        printf("CURRENTLY ON (%d, %d)\n", currentY, currentX);
        assert( currentX >= 0 );
        assert( currentY >= 0 );
        maze->grid[currentY][currentX] = '*';
        tempX = currentX;
        tempY = currentY;
        currentX = maze->prevX[tempY][tempX];
        currentY = maze->prevY[tempY][tempX];
    }
}

// void DFS(Maze *maze){

//     Queue q;
//     initQueue(&q);
//     Cell start;
//     start.y = maze->startY;
//     start.x = maze->startX;

//     enqueue(&q, start);

//     // Arrays to represent possible movements (up, down, left, right)
//     int dx[] = {0, 0, -1, 1};
//     int dy[] = {-1, 1, 0, 0};
//     while (!isEmpty(&q) ) {
//         Cell current = dequeueLIFO(&q);
//         printf("jestem na (%d,%d)\n", current.y, current.x);
//         maze->visited[current.y][current.x] = true;
//         if (current.x == maze->endX && current.y == maze->endY) {
//             printPrev(maze);
//             markPath(maze);
//             printf("Path found!\n");
//             return; // Reached the destination
//         }

//         // Explore adjacent cells
//         for (int i = 0; i < 4; i++) {
//             int nx = current.x + dx[i];
//             int ny = current.y + dy[i];
//             if (isValidCell(maze, nx, ny) && !maze->visited[ny][nx]) {
//                 printf("Dodaje do kolejki (%d, %d) \n", ny, nx);
//                 enqueue(&q, (Cell){nx, ny});
//                 maze->prevY[ny][nx] = current.y; // Store the previous cell for each cell in the path
//                 maze->prevX[ny][nx] = current.x; // Store the previous cell for each cell in the path
//                 printf("Prev (%d,%d) to (%d,%d) \n", ny, nx, current.y, current.x);
//             }
//         }
//         printf("WIUUM Prev (1,1) to (%d,%d) \n", maze->prevY[1][1], maze->prevX[1][1]);

//     }

//     // If the end cell is unreachable
//     printf("Path not found\n");

// }
