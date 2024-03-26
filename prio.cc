#include "prio.h"
#include <algorithm>
#include <iostream>

KaryHeap::KaryHeap(int k) : k(k) {
    if (k <= 1) {
        throw std::invalid_argument("k must be greater than 1");
    }
}

void KaryHeap::insert(int element) {
    heap.push_back(element);
    heapifyUp(heap.size() - 1);
}

int KaryHeap::extractMin() {
    if (heap.empty()) {
        throw std::length_error("Heap is empty");
    }
    int minElement = heap.front();
    heap.front() = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return minElement;
}

void KaryHeap::printHeap() const {
    for (int element : heap) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int KaryHeap::parent(int i) const {
    return (i - 1) / k;
}

int KaryHeap::child(int i, int childIndex) const {
    return k * i + childIndex + 1;
}

void KaryHeap::heapifyDown(int i) {
    int smallest = i;
    for (int j = 1; j <= k; ++j) {
        int c = child(i, j);
        if (c < heap.size() && heap[c] < heap[smallest]) {
            smallest = c;
        }
    }

    if (smallest != i) {
        std::swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}

void KaryHeap::heapifyUp(int i) {
    while (i > 0 && heap[parent(i)] > heap[i]) {
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

int main() {
    int k = 3;
    KaryHeap heap(k);

    for (size_t i = 0; i < 10000000; i++)
    {
        heap.insert(i);
    }
    

    std::cout << "Heap elements: ";
    heap.printHeap();

    int min = heap.extractMin();
    std::cout << "Extracted minimum element: " << min << std::endl;

    std::cout << "Heap after extraction: ";
    heap.printHeap();


    std::cout << "Press ENTER to exit.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
}