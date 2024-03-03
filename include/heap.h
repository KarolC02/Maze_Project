#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>

typedef struct {
    int x, y, distance;
} Node;

typedef struct {
    Node* nodes;
    int size;
    int capacity;
} MinHeap;

void initHeap(MinHeap* heap, int capacity);
void insert(MinHeap* heap, Node node);
Node Poll(MinHeap* heap);
void decreaseKey(MinHeap* heap, int x, int y, int distance);
void freeHeap(MinHeap* heap);

#endif // HEAP_HS
