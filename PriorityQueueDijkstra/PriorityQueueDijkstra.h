#pragma once
#include "../Vector/Vector.h"
#include "../Graph/graphNode.h"
#include "../String/String.h"
#include "DijkstraNode.h"

class PriorityQueueDijkstra {

    Vector<DijkstraNode> vec;

    size_t parent(size_t index);

    size_t left(size_t index);

    size_t right(size_t index);

    void heapifyUp(size_t i);

    void heapifyDown(size_t i);

    public:

    bool empty();

    void push(DijkstraNode ptr);

    void pop();

    DijkstraNode top();

    size_t size();

};


