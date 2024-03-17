// #include <limits.h>
// #include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <assert.h>

// // void BFS(void)
// //     printf("HELLO WORLD\n");
// // }

// void BFS(Maze *maze){

//     Queue q;
//     initQueue(&q);
//     Cell prev[maze->height][maze->width];

//     Cell start = {1, 0};

//     int currentX = 0;
//     int currentY = 0;

//     maze->visited[currentY][currentX] = true;
//     enqueue(&q, start);

//     // Arrays to represent possible movements (up, down, left, right)
//     int dx[] = {0, 0, -1, 1};
//     int dy[] = {-1, 1, 0, 0};

//     while (!isQueueEmpty(&q)) {
//         Cell current = dequeueFIFO(&q);


//         if (current.x == maze->endX && current.y == maze->endY) {
//             printf("A tu byłem??\n");
//             printPrev(prev, maze->width, maze->height);
//             markPath(maze->grid, current.x, current.y, prev);
//             printf("Path found!\n");
//             return; // Reached the destination
//         }

//        // Explore adjacent cells
//         for (int i = 0; i < 4; i++) {
//             int nx = current.x + dx[i];
//             int ny = current.y + dy[i];
//             printf("NO WITAM1\n");
//             if (isValidCell(maze, nx, ny) && !maze->visited[ny][nx]) {
//                 printf("NO WITAM2\n");
//                 maze->visited[ny][nx] = true;
//                 enqueue(&q, (Cell){nx, ny});
//                 prev[ny][nx] = current; // Store the previous cell for each cell in the path
//            }
//        }
//        printf("A jestem na (%d,%d)\n\n", current.x, current.y);
//    }

//    // If the end cell is unreachable
//    printf("Path not found\n");
// }