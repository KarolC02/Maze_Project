#include "DFS.h"
#include "maze.h"
#include <stdio.h>

void DFS(Maze *maze){

    Queue q;
    initQueue(&q);
    Cell start;
    start.y = maze->startY;
    start.x = maze->startX;

    enqueue(&q, start);

    // Arrays to represent possible movements (up, down, left, right)
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    while (!isEmpty(&q) ) {
        Cell current = dequeueLIFO(&q);
        maze->visited[current.y][current.x] = true;
        if (current.x == maze->endX && current.y == maze->endY) {
            printPrev(maze);
            markPath(maze);
            printf("Path found!\n");
            return; // Reached the destination
        }

        // Explore adjacent cells
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (isValidCell(maze, nx, ny) && !maze->visited[ny][nx]) {
                enqueue(&q, (Cell){nx, ny});
                maze->prevY[ny][nx] = current.y; // Store the previous cell for each cell in the path
                maze->prevX[ny][nx] = current.x; // Store the previous cell for each cell in the path
            }
        }
    }

    // If the end cell is unreachable
    printf("Path not found\n");

}