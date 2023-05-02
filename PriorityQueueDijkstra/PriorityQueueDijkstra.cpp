#include "PriorityQueueDijkstra.h"

void swapd(DijkstraNode* d1, DijkstraNode* d2) {

    DijkstraNode temp(*d1);

    *d1 = *d2;
    *d2 = temp;

}

size_t PriorityQueueDijkstra::left(size_t index) { return (index*2) + 1; }

size_t PriorityQueueDijkstra::right(size_t index) { return (index*2) + 2; }

size_t PriorityQueueDijkstra::parent(size_t index) { return (index-1)/2; }

size_t PriorityQueueDijkstra::size() { return vec.size(); }

DijkstraNode PriorityQueueDijkstra::top() { return vec[0]; }

bool PriorityQueueDijkstra::empty() { return vec.size() == 0; }


void PriorityQueueDijkstra::push(DijkstraNode ptr) {

    vec.pushBack(std::move(ptr));
    heapifyUp(size() - 1);

}

void PriorityQueueDijkstra::pop() {

    vec[0] = vec[--vec._size];
    heapifyDown(0);

}

void PriorityQueueDijkstra::heapifyUp(size_t i) {

    if (i && vec[parent(i)].weigth > vec[i].weigth) {
        //std::swap(vec[i], vec[parent(i)]);
        swapd(&vec[i], &vec[parent(i)]);
        heapifyUp(parent(i));
    }

}

void PriorityQueueDijkstra::heapifyDown(size_t i) {

    int smallest = i;
    if (left(i) < size() && vec[left(i)].weigth < vec[smallest].weigth)
        smallest = left(i);
    if (right(i) < size() && vec[right(i)].weigth < vec[smallest].weigth)
        smallest = right(i);
    if (smallest != i) {
        //std::swap(vec[i], vec[smallest]);
        swapd(&vec[i], &vec[smallest]);
        heapifyDown(smallest);
    }

}