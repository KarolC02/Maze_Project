#ifndef A_STAR_H
#define A_STAR_H

#include "graph_utils.h"

#define MAX_SIZE 1024

int calculateHeuristic(int x, int y, int goalX, int goalY);
void AStar(Maze *maze);


#endif // A_STAR_H
