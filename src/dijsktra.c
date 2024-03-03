#include "dijsktra.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

void dijkstra(int startX, int startY, int endX, int endY, char maze[MAX_SIZE][MAX_SIZE], int width, int height) {

    printf("NO SIEMA");
    int distances[MAX_SIZE][MAX_SIZE];
    bool visited[MAX_SIZE][MAX_SIZE];
    int prev[MAX_SIZE * MAX_SIZE][2];



    // Initialize distances, visited, and previous node arrays
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            distances[i][j] = INT_MAX;
            visited[i][j] = false;
            prev[i * width + j][0] = -1;
            prev[i * width + j][1] = -1;
        }
    }

    MinHeap heap;
    initHeap(&heap, MAX_SIZE * MAX_SIZE);
    distances[startY][startX] = 0;
    insert(&heap, (Node){startX, startY, 0});

    while (heap.size > 0) {
        Node current = Poll(&heap);
        if (visited[current.y][current.x]) {
            continue;
        }

        visited[current.y][current.x] = true;

        if (current.x == endX && current.y == endY) {
            break; // Reached the destination
        }

        // Add neighboring nodes to the heap
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Right, Down, Left, Up
        for (int i = 0; i < 4; ++i) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height && maze[ny][nx] != 'X' && !visited[ny][nx]) {
                int newDist = distances[current.y][current.x] + 1;
                if (newDist < distances[ny][nx]) {
                    distances[ny][nx] = newDist;
                    prev[ny * width + nx][0] = current.x;
                    prev[ny * width + nx][1] = current.y;
                    insert(&heap, (Node){nx, ny, newDist});
                }
            }
        }
    }

    reconstruct_path(prev, endX, endY, maze);
    freeHeap(&heap);
}

void reconstruct_path(int prev[MAX_SIZE * MAX_SIZE][2], int currentX, int currentY, char maze[MAX_SIZE][MAX_SIZE]) {
    // Starting from the end node, we will go back through the previous nodes to find the path
    while (currentX != -1 && currentY != -1) {
        maze[currentY][currentX] = '*'; // Mark the path
        int tempX = prev[currentY * MAX_SIZE + currentX][0];
        int tempY = prev[currentY * MAX_SIZE + currentX][1];
        currentX = tempX;
        currentY = tempY;
    }
}
