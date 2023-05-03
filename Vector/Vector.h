#pragma once
#include <cstddef>
#include <utility>

template<typename T>
class Vector {

    T* buffer;

    public:

    size_t _size;
    size_t _capacity;

    Vector();

    Vector(size_t cap);

    Vector(const Vector<T>& other);

    ~Vector();

    void pushBack(T data);

    size_t size() const;

    size_t capacity() const;

    const T* getBuffer() const;

    void resize(size_t newSize);

    Vector<T>& operator=(const Vector<T>& other);

    T operator[](size_t index) const;

    T& operator[](size_t index);

};

template<typename T>
Vector<T>::Vector() : _size(), _capacity(), buffer(nullptr) {}

template<typename T>
Vector<T>::Vector(size_t cap) : _size(), _capacity(cap), buffer(new T[cap]) {}

template<typename T>
Vector<T>::Vector(const Vector<T> &other) {

    _capacity = other._capacity;
    _size = other.size();
    buffer = new T[_capacity];
    for(int i = 0; i < _size; i++) { buffer[i] = other[i]; }

}

template<typename T>
Vector<T>::~Vector() {

    _size = 0;
    _capacity = 0;
    delete[] buffer;

}

template<typename T>
size_t Vector<T>::size() const { return _size; }

template<typename T>
size_t Vector<T>::capacity() const { return _capacity; }

template<typename T>
const T* Vector<T>::getBuffer() const { return buffer; }

template<typename T>
T& Vector<T>::operator[](size_t index) { return buffer[index]; }

template<typename T>
T Vector<T>::operator[](size_t index) const { return buffer[index]; }

template<typename T>
void Vector<T>::resize(size_t newSize) {

    T* newBuff = new T[newSize];

    for(int i = 0; i < _size; i++) { newBuff[i] = std::move(buffer[i]); }

    delete[] buffer;
    buffer = newBuff;
    _capacity = newSize;

}

template<typename T>
void Vector<T>::pushBack(T data) {

    if(_capacity == 0) { _capacity = 1; }

    if(_size + 1 >= _capacity) { resize(_capacity*2); }

    buffer[_size++] = std::move(data);

}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &other) {

    Vector<T> newVec(other);
    return newVec;

}

