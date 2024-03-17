#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void printMaze( Maze *maze ){
    if ( maze == NULL ){
        fprintf(stderr, "Error loading the maze");
        exit(EXIT_FAILURE);
    }
    for( int i = 0; i < maze->height; i++ ){
        for( int j = 0; j < maze->width; j++ ){
            printf("%c", maze->grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
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
            fprintf(stderr, "Found illegal character while parsing: %d\n", ch);
            exit(EXIT_FAILURE);
        }

        else if (ch == '\n') {
            current_x = 0;
            current_y ++ ;
            height++;
        } else {
            maze->grid[current_y][current_x] = ch;

            if (ch == 'P') {
                printf("Found P at (%d, %d)\n", current_y, current_x);
                maze->startX = current_x;
                maze->startY = current_y;
                P_set = 1;
            } else if (ch == 'K') {
                printf("Found K at (%d, %d)\n", current_y, current_x);
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
    assert (height > 2);
    assert (width > 2);
    maze->height = height;
    maze->width = width;
    maze->prevX = (int **)malloc(maze->height * sizeof(int *));
    maze->prevY = (int **)malloc(maze->height * sizeof(int *));
    maze->visited = (bool **)malloc(maze->height * sizeof(bool *));
    assert (maze->prevX != NULL );
    assert (maze->prevY != NULL );
    assert (maze->visited != NULL) ;

    if (maze->prevX == NULL || maze->prevY == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < maze->height; ++i) {
        maze->prevX[i] = (int *)malloc(maze->width * sizeof(int));
        maze->prevY[i] = (int *)malloc(maze->width * sizeof(int));
        maze->visited[i] = (bool *)malloc(maze->height * sizeof(bool));
        assert (maze->prevX[i] != NULL );
        assert (maze->prevY[i] != NULL );
        assert (maze->visited[i] != NULL) ;

        if (maze->prevX[i] == NULL || maze->prevY[i] == NULL ) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        for(int j = 0; j < maze->width; j++ ){
            maze->prevX[i][j] = -1;
            maze->prevY[i][j] = -1;
            if(maze->grid[i][j] == 'X')
                maze->visited[i][j] = true;
            else
                maze->visited[i][j] = false;
        }
    }

    if ( P_set == 0 || K_set == 0 ){
        fprintf(stderr, "Haven't found a starting or an ending point\n");
        exit(EXIT_FAILURE);
    }
    // return error if there is not starting point or exit

}
