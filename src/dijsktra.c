#include "dijsktra.h"
#include "graph_utils.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

void dijkstra(Maze *maze){
    // Initialize distances, maze->visited, and previous node arrays
    int **distances = (int**)malloc(maze->height * sizeof(int * ) );

    assert (maze->prevX != NULL);
    assert (maze->prevX != NULL);
    if (distances == NULL || maze->visited == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // Allocate memory for each row of prevX and prevY
    for (int i = 0; i < maze->height; ++i) {
        assert (maze->prevX[i] != NULL);
        assert (maze->prevY[i] != NULL);
        distances[i] = (int *)malloc(maze->width * sizeof(int));

        if (distances[i] == NULL || maze->visited[i] == NULL) {
            fprintf(stderr, "Memory allocation failed heeeere?\n");
            exit(EXIT_FAILURE);
        }

        for(int j = 0; j < maze->width; j++ ){
            distances[i][j] = INT_MAX;
            assert (maze->prevX[i] != NULL);
            assert (maze->prevX[i] != NULL);
        }
    }

    MinHeap heap;
    initHeap(&heap, MAX_SIZE * MAX_SIZE);
    distances[maze->startX][maze->startY] = 0;
    insert(&heap, (Node){maze->startX, maze->startY, 0, 0});
    
    // printf("The size of the heap is now %d\n", heap.size)
    while (heap.size > 0) {
        Node current = Poll(&heap);
        // printf("The size of the heap is now %d\n", heap.size);
        // printf("Aktualnie jestem na (%d,%d)\n", current.y, current.x);

        if (maze->visited[current.y][current.x]) {
            // printf("JUŻ TU BYŁEM\n");
            // printf("A jestem na (%d,%d)\n\n", current.y,current.x);
            continue;
        }


        maze->visited[current.y][current.x] = true;
        if (current.x == maze->endX && current.y == maze->endY) {
            // printf("JUPOIIASIDIA\n\n");
            break; // Reached the destination
        }

        // Add neighboring nodes to the heap
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Right, Down, Left, Up
        // printf("Currently at node (%d, %d)\n", current.y, current.x);

        for (int i = 0; i < 4; ++i) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];
            // printf("Currently checking if I can go to (%d, %d)\n", ny, nx);

            if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height && maze->grid[ny][nx] != 'X' && !maze->visited[ny][nx]) {
                // printf("I'm procsessing (%d,%d)\n", ny, nx);
                // printf("I just went to (%d, %d)", ny, nx);
                int newDist = distances[current.y][current.x] + 1;
                if (newDist < distances[ny][nx]) {
                    distances[ny][nx] = newDist;
                    maze->prevX[ny][nx] = current.x;
                    maze->prevY[ny][nx] = current.y;
                    // printf("PREV OF (%d,%d) is (%d,%d)\n", ny, nx, prevY[ny][nx], prevX[ny][nx]);
                    insert(&heap, (Node){nx, ny, newDist, newDist});
                    // printf("Just inserted a node! The size of the heap is now %d\n", heap.size);
                }
            }
        }
    }

    markPath(maze);
    freeHeap(&heap);


}