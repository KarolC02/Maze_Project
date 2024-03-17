#include "maze.h"
#include "graph_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void rightHandRule(Maze *maze) {
    // Assuming direction indices: 0=up, 1=right, 2=down, 3=left
    int direction = 1; // Start facing right
    int currentX = maze->startX;
    int currentY = maze->startY;

    // Direction vectors: right, down, left, up
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    while (currentX != maze->endX || currentY != maze->endY) {
        bool moved = false;
        int nextDir = direction;
        for (int i = 0; i < 4; ++i) {
            nextDir = (direction + i + 3) % 4; // Rotate right priority, including current direction as fallback
            int nextX = currentX + dx[nextDir];
            int nextY = currentY + dy[nextDir];

            // Check move validity: within bounds and not a wall
            if (nextX >= 0 && nextX < maze->width && nextY >= 0 && nextY < maze->height && maze->grid[nextY][nextX] != 'X') {
                // Update prev arrays before moving
                maze->prevX[nextY][nextX] = currentX;
                maze->prevY[nextY][nextX] = currentY;

                // Move to the next cell
                currentX = nextX;
                currentY = nextY;
                direction = nextDir; // Update direction after successful move
                moved = true;
                break;
            }
        }

        if (!moved) {
            // If stuck or maze incorrectly configured, might need special handling
            printf("Can't move - check maze configuration or end condition.\n");
            return;
        }
    }

    // If needed, you can now reconstruct the path from the end to the start by tracing back through prevX and prevY
    printf("Exit found!\n");
    printPrev(maze);
    markPath(maze);
}
