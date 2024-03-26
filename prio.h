#ifndef PRIO_H
#define PRIO_H

#include <vector>
#include <stdexcept>

class KaryHeap {
public:
    explicit KaryHeap(int k);
    void insert(int element);
    int extractMin();
    void printHeap() const;

private:
    std::vector<int> heap;
    int k;

    int parent(int i) const;
    int child(int i, int childIndex) const;
    void heapifyDown(int i);
    void heapifyUp(int i);
};

#endif
