#include "dijsktra.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generate_random_number(int oldNumber) {
    int newNumber = rand() % 4;
    while (newNumber == oldNumber){
        srand(time(NULL));
        newNumber = rand() % 4;
    }

    return newNumber;
}


void randomPath(Maze *maze){

    int currentX = 1;
    int currentY = 1;
    int randomDirection = generate_random_number(5);

    while (true){
        if (currentX == maze->endX && currentY == maze->endY) {
            printf("JUPOIIASIDIA\n\n");
            break; // Reached the destination
        }
        maze->grid[currentY][currentX] = '*';
        if (randomDirection == 0){
            if (maze->grid[currentY][currentX+1] != 'X' && maze->grid[currentY][currentX+1] != 'P'){
                currentX++;
            }
        }
        if (randomDirection == 1){
            if (maze->grid[currentY+1][currentX] != 'X' && maze->grid[currentY+1][currentX] != 'P'){
                currentY++;
            }
        }
        if (randomDirection == 2){
            if (maze->grid[currentY][currentX-1] != 'X' && maze->grid[currentY][currentX-1] != 'P'){
                currentX--;
            }
        }
        if (randomDirection == 3){
            if (maze->grid[currentY-1][currentX] != 'X' && maze->grid[currentY-1][currentX] != 'P'){
                currentY--;
            }
        }
        randomDirection = generate_random_number(randomDirection);
        //printf("A jestem na (%d,%d)\n\n", currentY,currentX);
    }

}