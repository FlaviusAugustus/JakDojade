#pragma once
#include "../String/String.h"

template<typename T>
struct HashNode {

    T value;
    String key;

    HashNode() : value(),  key() {}

    HashNode(T i, char* c) : value(std::move(i)), key(c) {

    }

};
