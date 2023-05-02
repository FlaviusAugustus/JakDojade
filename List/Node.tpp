#include "Node.h"
#include <iostream>

template <typename T> Node<T>::Node(T data) : data(data), next(nullptr) {}

template <typename T> Node<T>::Node() : data(), next(nullptr) {}

