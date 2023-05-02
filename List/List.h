#pragma once
#include <iostream>
#include "Node.h"


template <typename T>
class List {

    Node<T>* first;
    Node<T>* last;
    size_t size;

public:

    ~List();

    List();

    List(const List<T>& other);

    List(List<T>&& other);

    void addFirst(T data);

    void pushBack(T data);

    void removeFirst();

    void removeLast();

    void clear();

    Node<T>* getAt(size_t pos) const;

    Node<T>* getFirst() const;

    Node<T>* getLast() const;

    size_t length() const;

    bool isEmpty() const;

    List<T>& operator=(const List<T>& other);

    template<class H> friend std::ostream& operator<<(std::ostream& out, const List<H>& list);

};

#include "List.tpp"