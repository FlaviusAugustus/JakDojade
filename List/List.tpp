#include <iostream>
#include "List.h"

template<typename T> List<T>::List() : size() , first(nullptr), last(nullptr) {}

template<typename T> List<T>::List(const List& other) {

    if(!other.first) { first = nullptr; last = nullptr; size = 0;
        return;}

    size = other.size;
    const Node<T>* tmpNode = other.first;

    first = new Node<T>;
    Node<T>* node = first;
    first->data = tmpNode->data;

    for(int i = 0; i < size -1; i++) {

        node->next = new Node<T>(tmpNode->next->data);
        node = node->next;
        tmpNode = tmpNode->next;

    }

}

template<typename T> List<T>::List(List&& other) {

    first = other.first;
    size = other.size;

    other.first = nullptr;
    other.size = 0;

}

template<typename T> void List<T>::clear() {

    Node<T>* toDelete;

    while(first) {

        toDelete = first;
        first = first->next;
        delete toDelete;

    }

    first = nullptr;
    last = nullptr;
    size = 0;

}

template<typename T> List<T>::~List() {

    clear();

}

template<typename T> void List<T>::addFirst(T data) {

    auto newNode = new Node<T>(data);
    newNode->next = first;
    first = newNode;

    if(size == 0) { last = first; }

    size++;
}

template<typename T> void List<T>::pushBack(T data) {

    auto newNode = new Node<T>(std::move(data));

    if(size > 0) {

        last->next = newNode;

    }

    last = newNode;

    if(size == 0) { first = last; }

    size++;
}

template<typename T> void List<T>::removeFirst() {

    if(size == 0) { return; }
    if(size == 1) { clear(); }

    Node<T>* toDelete = first;
    if(!toDelete) return;
    first = first->next;

    delete toDelete;

    size--;
}

template<typename T> void List<T>::removeLast() {

    if(size == 0) { return; }
    if(size == 1 || !first->next) { clear(); return;}

    Node<T>* toDelete = last;
    Node<T>* newLast = first;

    if(!newLast || !toDelete) { return; }

    for(;newLast->next && newLast->next->next; newLast = newLast->next) {}

    last = newLast;
    last->next = nullptr;

    if(!toDelete) return;

    delete toDelete;

    size--;

}

template<typename T> Node<T>* List<T>::getAt(size_t pos) const {

    if(pos > size) { return nullptr; }

    Node<T>* iter = first;
    for(int i = 0; i < pos - 1; i++) { iter = iter->next; }

    return iter;

}

template<typename T> Node<T>* List<T>::getLast() const { return last; }

template<typename T> Node<T>* List<T>::getFirst() const { return first; }

template<typename T> size_t List<T>::length() const { return size; }

template<typename T> bool List<T>::isEmpty() const { return size == 0; }

template<typename T> std::ostream& operator<<(std::ostream& out, const List<T>& list) {

    Node<T>* tmp = list.first;

    while (tmp) {

        out << tmp->data;
        tmp = tmp->next;

    }

    return out;

}

template<typename T> List<T>& List<T>::operator=(const List<T>& other) {

    if (this == &other) { return *this; }

    List<T> tmp(other);

    std::swap(first, tmp.first);
    std::swap(size, tmp.size);

    return *this;

}
