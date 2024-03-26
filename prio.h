#ifndef PRIO_H
#define PRIO_H

#include <stdexcept>

// This is an implementation of the k-ary heap as requested from the assignment.
// It can have 'k' amount of children per node, defaulted to 3 in code.
class KaryHeap {
public:
    // This constructor creates a heap (with k children per node)
    // Have an initial capacity for the array, that increases in size as needed.
    explicit KaryHeap(int k, size_t capacity);

    // This destructor deletes the memory from the heap.
    ~KaryHeap();

    // This inserts an element into the heap
    void insert(int element);

    // This extracts the lowest element in the heap
    int extractMin();

    // This prints out the elements in the heap.
    // Not currently in use, mostly for debugging.
    void printHeap() const;

private:
    int* heap; // Dynamic array to store elements
    size_t size; // Current number of elements in the heap.
    size_t capacity; // Current maximum capacity of the heap array.
    int k; // Number of children per node

    // This makes sure that the heap has enough room before adding in more elements
    // Makes room for more elements if not enough room
    void ensureCapacity();

    // This returns the index of the parent node at the given index
    int parent(int i) const;

    // This returns the index of the j-th child, at the given index.
    int child(int i, int childIndex) const;

    // This brings back the heap by moving the element at the given index
    // down the heap
    void heapMoveDown(int i);

    // This brings back the heap by moving the element at the given index
    // up the heap
    void heapMoveUp(int i);
};

#endif