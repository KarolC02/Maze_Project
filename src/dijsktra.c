#include "dijsktra.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>

// Directions are encoded as Right, Down, Left, Up
static const int DX[4] = {1, 0, -1, 0};
static const int DY[4] = {0, 1, 0, -1};
static const char* DIRECTION_NAMES[4] = {"RIGHT", "DOWN", "LEFT", "UP"};

void dijsktra(Maze *maze) {
    // Initialize distance array and heap
    int **distances = malloc(maze->height * sizeof(int *));
    assert(distances != NULL);

    for (int i = 0; i < maze->height; ++i) {
        distances[i] = malloc(maze->width * sizeof(int));
        assert(distances[i] != NULL);
        for (int j = 0; j < maze->width; j++) {
            distances[i][j] = INT_MAX;
        }
    }

    MinHeap heap;
    initHeap(&heap, maze->height * maze->width);
    distances[maze->startY][maze->startX] = 0;
    insert(&heap, (Node){maze->startX, maze->startY, 0});

    while (heap.size > 0) {
        Node current = Poll(&heap);

        if (maze->visited[current.y][current.x]) {
            continue;
        }

        maze->visited[current.y][current.x] = true;
        if (current.x == maze->endX && current.y == maze->endY) {
            break; // Reached the destination
        }

        // Explore neighboring nodes
        for (int i = 0; i < 4; ++i) {
            int nx = current.x + DX[i];
            int ny = current.y + DY[i];

            if (nx >= 0 && nx < maze->width && ny >= 0 && ny < maze->height &&
                maze->grid[ny][nx] != 'X' && !maze->visited[ny][nx]) {
                int newDist = distances[current.y][current.x] + 1;
                if (newDist < distances[ny][nx]) {
                    distances[ny][nx] = newDist;
                    maze->prevX[ny][nx] = current.x;
                    maze->prevY[ny][nx] = current.y;
                    insert(&heap, (Node){nx, ny, newDist});
                }
            }
        }
    }

    markPathWithDistances(maze, distances);
    freeHeap(&heap);
    freeDistances(distances, maze->height);
}

void markPathWithDistances(Maze *maze, int **distances) {
    int x = maze->endX, y = maze->endY;
    int prevDirection = -1, steps = 0;

    printf("START\n");
    while (x != maze->startX || y != maze->startY) {
        int px = maze->prevX[y][x];
        int py = maze->prevY[y][x];
        int directionIndex = getDirectionIndex(px, py, x, y);

        if (prevDirection == -1 || directionIndex == prevDirection) {
            steps++;
        } else {
            printf("FORWARD %d\n", steps);
            printf("TURN%s\n", getTurnDirection(prevDirection, directionIndex));
            steps = 1;
        }

        prevDirection = directionIndex;
        x = px;
        y = py;
    }
    if (steps > 0) {
        printf("FORWARD %d\n", steps);
    }
    printf("STOP\n");
}

int getDirectionIndex(int px, int py, int x, int y) {
    for (int i = 0; i < 4; ++i) {
        if (x - px == DX[i] && y - py == DY[i]) {
            return i;
        }
    }
    return -1; // Should not happen
}

const char* getTurnDirection(int from, int to) {
    int diff = (to - from + 4) % 4;
    if (diff == 1) {
        return "LEFT";
    } else if (diff == 3) {
        return "RIGHT";
    }
    return "";
}

void freeDistances(int **distances, int height) {
    for (int i = 0; i < height; ++i) {
        free(distances[i]);
    }
    free(distances);
}

void printPath(Maze *maze) {
    int x = maze->endX;
    int y = maze->endY;
    int direction = -1;
    int count = 0;

    printf("START\n");

    while (x != maze->startX || y != maze->startY) {
        int prev_x = maze->prevX[y][x];
        int prev_y = maze->prevY[y][x];
        int new_direction = getDirectionIndex(prev_x, prev_y, x, y);

        if (new_direction != direction) {
            if (count > 0) {
                printf("FORWARD %d\n", count);
            }
            if (direction != -1) {
                printf("TURN%s\n", getTurnDirection(direction, new_direction));
            }
            count = 0;
            direction = new_direction;
        }
        count++;
        x = prev_x;
        y = prev_y;
    }

    if (count > 0) {
        printf("FORWARD %d\n", count);
    }
    printf("STOP\n");
}