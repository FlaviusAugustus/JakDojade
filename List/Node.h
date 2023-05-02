#pragma once

template <typename T>
struct Node {

    T data;
    Node* next;

    Node();

    Node(T data);

    ~Node() = default;

};

#include "Node.tpp"