#include "Node.h"
#include <utility>
#include <iostream>

template <typename T> Node<T>::Node(T data) : data(std::move(data)), next(nullptr) {}

template <typename T> Node<T>::Node() : data(), next(nullptr) {}

