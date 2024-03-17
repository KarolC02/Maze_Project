#ifndef MAZE_H
#define MAZE_H

#define MAX_SIZE 1024

// The maze structure
typedef struct {
    char grid[MAX_SIZE][MAX_SIZE];
    int **prevX;
    int **prevY;
    int width;
    int height;
    int startX;
    int startY;
    int endX;
    int endY;
} Maze;

// Function prototypes
void readMazeFromFile(const char *filename, Maze *maze);
void printMaze( Maze *maze );

#endif // MAZE_H
