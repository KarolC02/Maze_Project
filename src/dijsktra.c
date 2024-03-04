#include "dijsktra.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

void dijkstra2(Maze *maze){
    // Initialize distances, visited, and previous node arrays
    int **distances = (int**)malloc(maze->height * sizeof(int * ) );
    bool **visited = (bool**)malloc(maze->width * sizeof(bool*) );
    if (distances == NULL || visited == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }


    int **prevX = (int **)malloc(maze->height * sizeof(int *));
    int **prevY = (int **)malloc(maze->height * sizeof(int *));

    if (prevX == NULL || prevY == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for each row of prevX and prevY
    for (int i = 0; i < maze->height; ++i) {
        prevX[i] = (int *)malloc(maze->width * sizeof(int));
        prevY[i] = (int *)malloc(maze->width * sizeof(int));

        distances[i] = (int *)malloc(maze->width * sizeof(int));
        visited[i] = (bool *)malloc(maze->width * sizeof(bool));

        if (prevX[i] == NULL || prevY[i] == NULL || distances[i] == NULL || visited[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        for(int j = 0; j < maze->width; j++ ){
            distances[i][j] = INT_MAX;
            visited[i][j] = false;
            prevX[i][j] = -1;
            prevY[i][j] = -1;
            // If it's a wall mark it as visited
            if( maze->grid[i][j] == 'X' ){
                visited[i][j] = true;
            }
        }
    }

    MinHeap heap;
    initHeap(&heap, MAX_SIZE * MAX_SIZE);
    distances[maze->startX][maze->startY] = 0;
    insert(&heap, (Node){maze->startX, maze->startY, 0});
    
    printf("THe size of the heap is now %d\n", heap.size);
    while (heap.size > 0) {
        Node current = Poll(&heap);
        printf("THe size of the heap is now %d\n", heap.size);
        printf("Aktualnie jestem na (%d,%d)\n", current.y, current.x);

        if (visited[current.y][current.x]) {
            printf("JUŻ TU BYŁEM\n");
            printf("A jestem na (%d,%d)\n\n", current.y,current.x);
            continue;
        }

        visited[current.y][current.x] = true;

        if (current.x == maze->endX && current.y == maze->endY) {
            printf("JUPOIIASIDIA\n\n");
            break; // Reached the destination
        }

        // Add neighboring nodes to the heap
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Right, Down, Left, Up
        // printf("Currently at node (%d, %d)\n", current.y, current.x);
        for (int i = 0; i < 4; ++i) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];
            // printf("Currently checking if I can go to (%d, %d)\n", ny, nx);
            printf("I want to check if i can go to (%d,%d)\n\n", ny, nx);
            if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height && maze->grid[ny][nx] != 'X' && !visited[ny][nx]) {
                // printf("I just went to (%d, %d)", ny, nx);
                int newDist = distances[current.y][current.x] + 1;
                if (newDist < distances[ny][nx]) {
                    distances[ny][nx] = newDist;
                    prevX[ny][nx] = current.x;
                    prevY[ny][nx] = current.y;
                    printf("PREV OF (%d,%d) is (%d,%d)\n", ny, nx, prevX[ny][nx], prevY[ny][nx]);
                    insert(&heap, (Node){nx, ny, newDist});
                    printf("Just inserted a node! The size of the heap is now %d\n", heap.size);
                }
            }
        }
    }

    reconstruct_path(prevX, prevY, maze->endX, maze->endY, maze);
    freeHeap(&heap);


}

// void dijkstra(int startX, int startY, int endX, int endY, char maze[MAX_SIZE][MAX_SIZE], int width, int height) {

//     printf("NO SIEMA");
//     int distances[MAX_SIZE][MAX_SIZE];
//     bool visited[MAX_SIZE][MAX_SIZE];
//     int prev[MAX_SIZE * MAX_SIZE][2];



//     // Initialize distances, visited, and previous node arrays
//     for (int i = 0; i < height; ++i) {
//         for (int j = 0; j < width; ++j) {
//             distances[i][j] = INT_MAX;
//             visited[i][j] = false;
//             prev[i * width + j][0] = -1;
//             prev[i * width + j][1] = -1;
//         }
//     }

//     MinHeap heap;
//     initHeap(&heap, MAX_SIZE * MAX_SIZE);
//     distances[startY][startX] = 0;
//     insert(&heap, (Node){startX, startY, 0});

//     while (heap.size > 0) {
//         Node current = Poll(&heap);
//         if (visited[current.y][current.x]) {
//             continue;
//         }

//         visited[current.y][current.x] = true;

//         if (current.x == endX && current.y == endY) {
//             break; // Reached the destination
//         }

//         // Add neighboring nodes to the heap
//         int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Right, Down, Left, Up
//         for (int i = 0; i < 4; ++i) {
//             int nx = current.x + directions[i][0];
//             int ny = current.y + directions[i][1];

//             if (nx >= 0 && nx < width && ny >= 0 && ny < height && maze[ny][nx] != 'X' && !visited[ny][nx]) {
//                 int newDist = distances[current.y][current.x] + 1;
//                 if (newDist < distances[ny][nx]) {
//                     distances[ny][nx] = newDist;
//                     prev[ny * width + nx][0] = current.x;
//                     prev[ny * width + nx][1] = current.y;
//                     insert(&heap, (Node){nx, ny, newDist});
//                 }
//             }
//         }
//     }

//     reconstruct_path(prev, endX, endY, maze);
//     freeHeap(&heap);
// }

void reconstruct_path(int **prevX, int **prevY, int currentX, int currentY, Maze *maze) {
    // Starting from the end node, we will go back through the previous nodes to find the path
    while (currentX != -1 && currentY != -1) {
        if (maze->grid[currentY][currentX] != 'K' ){
            maze->grid[currentY][currentX] = '*'; // Mark the path
        }
        printf("curently at (%d,%d)\n", currentY, currentX);
        int tempX = prevX[currentY][currentX];
        int tempY = prevY[currentY][currentX];
        if( maze->grid[tempY][tempX] == 'P'){
            break;
        }
        assert (tempX >= 0);
        assert (tempY >= 0);
        currentX = tempX;
        currentY = tempY;
        printf("Now at (%d,%d)\n", currentY, currentX);
    }
}
