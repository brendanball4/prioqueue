#include "prio.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <new>
#include <chrono>

// This is the constructor for KaryHeap, it initializes with k, and then sets the initial capacity.
// Throws error if k <= 1.
KaryHeap::KaryHeap(int k, size_t initialCapacity) : k(k), size(0), capacity(initialCapacity) {
    if (k <= 1) {
        throw std::invalid_argument("k must be greater than 1");
    }
    heap = new int[capacity]; // Set heap with initial capacity.
}

// This is the destructor implementation for KaryHeap, deletes the array from memory.
KaryHeap::~KaryHeap() {
    delete[] heap;
}

// This makes sure that there is enough room in the heap for more elements.
// If not, it doubles the array size.
void KaryHeap::ensureCapacity() {
    if (size >= capacity) {
        size_t newCapacity = capacity * 2; // Double the capacity.
        int* newHeap = new int[newCapacity]; // Create new heap with new capacity.
        std::copy(heap, heap + size, newHeap); // Copy the existing elements to the new heap.
        delete[] heap; // Delete old heap
        heap = newHeap; // Update the heap pointer to the new heap.
        capacity = newCapacity; // Update the capacity.
    }
}

// This inserts an element into the heap
void KaryHeap::insert(int element) {
    ensureCapacity(); // Make sure there is space for the new element.
    heap[size] = element; // Place the new element at the end of the heap.
    heapMoveUp(size); // Adjust the heap up.
    size++; // Increment the size of the heap.
}

// This extracts the lowest element in the heap
int KaryHeap::extractMin() {
    if (size == 0) {
        throw std::length_error("Heap is empty"); // Error if no elements in heap
    }
    int minElement = heap[0]; // The minimum element is at the root.
    heap[0] = heap[size - 1]; // Move the last element to the root.
    size--; // Reduce the size of the heap.
    heapMoveDown(0); // Adjust the heap down.
    return minElement; // Return the minimum element.
}

// This prints out the elements in the heap.
// Not currently in use, mostly for debugging.
void KaryHeap::printHeap() const {
    for (size_t i = 0; i < size; i++) {
        std::cout << heap[i] << " "; // Print the elements of heap
    }
    std::cout << std::endl;
}

// This returns the index of the parent node at the given index
int KaryHeap::parent(int i) const {
    return (i - 1) / k;
}

// This returns the index of the j-th child, at the given index.
int KaryHeap::child(int i, int childIndex) const {
    return k * i + childIndex + 1;
}

// This brings back the heap by moving the element at the given index
// down the heap
void KaryHeap::heapMoveDown(int i) {
    while (true) {
        int smallest = i; // Child node should be smallest.
        for (int j = 1; j <= k; ++j) { // Check all k children.
            int c = child(i, j); // Index of j-th child.
            if (c < size && heap[c] < heap[smallest]) { // Find the smallest among the node and its children.
                smallest = c;
            }
        }

        if (smallest != i) {
            std::swap(heap[i], heap[smallest]); // If not the smallest, swap with the smallest child.
            i = smallest; // Move to the smallest child's index and continue.
        } else {
            break; // If the smallest is the current node, the heap is good to go.
        }
    }
}

// This brings back the heap by moving the element at the given index
// up the heap
void KaryHeap::heapMoveUp(int i) {
    while (i > 0 && heap[parent(i)] > heap[i]) { // While not at the root and the parent is greater than the current node.
        std::swap(heap[i], heap[parent(i)]); // Swap with the parent.
        i = parent(i); // Move to the parent's index and continue.
    }
}


// Set the test size to 10 mill.
#define TEST_SIZE 100000000

int main() {
    // Set the nodes of the heap to 3 and the initial capacity to TEST_SIZE.
    int k = 3; 
    KaryHeap heap(k, TEST_SIZE);

    // Start timing the insertion process.
    auto startInsert = std::chrono::high_resolution_clock::now();
    // Insert the amount that is TEST_SIZE as elements into the heap.
    for (size_t i = 0; i < TEST_SIZE; ++i) {
        heap.insert(i);
    }
    // Stop timing the insertion process.
    auto endInsert = std::chrono::high_resolution_clock::now();
    // Calculate the duration of the insertion in microseconds and convert to seconds for display.
    std::chrono::duration<double, std::micro> insertTime = endInsert - startInsert;
    std::cout << "Time taken to insert " << TEST_SIZE << " elements: " << insertTime.count() / 1000000.0 << " seconds." << std::endl;

    // Start timing the extraction of the minimum element.
    auto startExtractMin = std::chrono::high_resolution_clock::now();
    // Take out the minimum element from the heap.
    int min = heap.extractMin();
    // Stop timing the extraction process.
    auto endExtractMin = std::chrono::high_resolution_clock::now();
    // Calculate the duration of the extraction in microseconds and convert to seconds for display.
    std::chrono::duration<double, std::micro> extractMinTime = endExtractMin - startExtractMin;
    std::cout << "Time taken to extract the minimum element: " << extractMinTime.count() / 1000000.0 << " seconds." << std::endl;
    // Display the extracted minimum element.
    std::cout << "Extracted minimum element: " << min << std::endl;

    // If needed, uncomment this code to see all the heap elements.
    // std::cout << "Heap after extraction: ";
    // heap.printHeap();

    // To prevent the console window from closing immediately after execution,
    // especially on Windows, wait for the user to press ENTER.
    // Might have to press 2 times, I am not sure why it does that.
    std::cout << "Press ENTER to exit.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}