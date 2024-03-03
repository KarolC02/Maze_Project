#include "maze.h"
#include <stdio.h>
#include <stdlib.h>

void readMazeFromFile(const char *filename, Maze *maze) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char ch;
    maze->width = 0;
    maze->height = 0;

    while (fscanf(file, "%c", &ch) != EOF) {
        if (ch == '\n') {
            if (maze->width == 0) {
                maze->width = maze->height; // Assuming square maze if width not set
            }
            maze->height++;
        } else {
            int x = maze->height;
            int y = maze->width;

            maze->grid[x][y] = ch;

            if (ch == 'P') {
                maze->startX = y;
                maze->startY = x;
            } else if (ch == 'K') {
                maze->endX = y;
                maze->endY = x;
            }

            maze->width++;
        }
    }

    fclose(file);
}
