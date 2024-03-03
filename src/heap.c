#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void initHeap(MinHeap* heap, int capacity) {
    heap->nodes = (Node*)malloc(sizeof(Node) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
}

void heapUp(MinHeap* heap, int idx) {
    while (idx != 0 && heap->nodes[(idx - 1) / 2].distance > heap->nodes[idx].distance) {
        swap(&heap->nodes[(idx - 1) / 2], &heap->nodes[idx]);
        idx = (idx - 1) / 2;
    }
}

void insert(MinHeap* heap, Node node) {
    if (heap->size == heap->capacity) {
        printf("Heap overflow\n");
        return;
    }
    
    heap->size++;
    int index = heap->size - 1;
    heap->nodes[index] = node;

    heapUp(heap, index);
}

void heapDown(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left].distance < heap->nodes[smallest].distance)
        smallest = left;
    if (right < heap->size && heap->nodes[right].distance < heap->nodes[smallest].distance)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->nodes[idx], &heap->nodes[smallest]);
        heapDown(heap, smallest);
    }
}

Node Poll(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return (Node){-1, -1, -1}; // Return an error value or handle error appropriately
    }
    
    Node root = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    heapDown(heap, 0);

    return root;
}

void decreaseKey(MinHeap* heap, int x, int y, int distance) {
    // This function assumes that the node to be decreased is already in the heap.
    // It searches for the node, updates its distance, and then performs a heap up
    // to maintain the heap property. Depending on your application, you may want to
    // optimize this process, especially if you can track nodes' positions in the heap.
    int i;
    for (i = 0; i < heap->size; i++) {
        if (heap->nodes[i].x == x && heap->nodes[i].y == y) {
            heap->nodes[i].distance = distance;
            break;
        }
    }
    if (i < heap->size) {
        heapUp(heap, i);
    }
}

void freeHeap(MinHeap* heap) {
    free(heap->nodes);
    heap->nodes = NULL;
    heap->size = 0;
    heap->capacity = 0;
}
