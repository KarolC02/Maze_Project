#include "../include/heap.h"
#include <stdio.h>
#include <assert.h>

void test_initHeap() {
    MinHeap heap;
    initHeap(&heap, 10); // Initialize the heap with capacity 10
    assert(heap.size == 0); // The size should be 0 after initialization
    assert(heap.capacity == 10); // The capacity should match the initialization value
    printf("test_initHeap passed.\n");
    freeHeap(&heap);
}

void test_decreaseKey() {
    MinHeap heap;
    initHeap(&heap, 10);

    insert(&heap, (Node){.x = 0, .y = 0, .distance = 5});
    insert(&heap, (Node){.x = 1, .y = 1, .distance = 10});
    decreaseKey(&heap, 1, 1, 2); // Decrease the distance of the node at (1,1) to 2

    assert(Poll(&heap).distance == 2); // Now, the node (1,1) should be the min
    printf("test_decreaseKey passed.\n");
    freeHeap(&heap);
}

void test_insert_and_min() {
    MinHeap heap;
    initHeap(&heap, 10);

    insert(&heap, (Node){.x = 0, .y = 0, .distance = 5});
    insert(&heap, (Node){.x = 1, .y = 1, .distance = 3});
    assert(heap.size == 2);
    Node min = Poll(&heap);
    assert(min.distance == 3); // The node with the smallest distance comes out first
    printf("test_insert_and_min passed.\n");
    freeHeap(&heap);
}


int main() {
    test_initHeap();
    test_insert_and_min();
    test_decreaseKey();
    printf("All heap tests passed.\n");
    return 0;
}
