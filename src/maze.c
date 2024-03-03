#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void readMazeFromFile(const char *filename, Maze *maze) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    assert (1 == 1);

    char ch;

    int current_x = 0;
    int current_y = 0;
    
    int P_set = 0;
    int K_set = 0;

    int height = 0;
    int width = 0;

    while (fscanf(file, "%c", &ch) != EOF) {

        // Check for illegal characters, only X, space, P, K, \n acceptable
        if (ch != 'X' && ch != ' ' && ch != 'K' && ch != 'P' && ch != '\n' ){
            fprintf(stderr, "Found illegal character while parsing: %c\n", ch);
            exit(EXIT_FAILURE);
        }


        else if (ch == '\n') {
            current_x = 0;
            current_y ++ ;
            height++;
        } else {

            maze->grid[current_x][current_y] = ch;

            if (ch == 'P') {
                maze->startX = current_x;
                maze->startY = current_y;
                P_set = 1;
            } else if (ch == 'K') {
                maze->endX = current_x;
                maze->endY = current_y;
                K_set = 1;
            }

            if ( current_y == 0 ){
                width ++;
            }

            current_x ++;
        }
    }

    fclose(file);

    if ( P_set == 0 || K_set == 0 ){
        fprintf(stderr, "Haven't found a starting or an ending point\n");
        exit(EXIT_FAILURE);
    }

    assert (height > 2);
    assert (width > 2);
    maze->height = height;
    maze->width = width;
    // return error if there is not starting point or exit

}
