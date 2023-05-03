#include "../List/List.h"
#include "HashNode.h"
#include "../Vector/Vector.h"

//hashmap accepts generic values, keys must be a string
template<typename T>
class HashMap {

    static const int HashSize;

    size_t count;
    size_t collisions;

public:

    Vector<String> keys;

    List<HashNode<T>>** buckets;

    unsigned long hash(const char* hashVal);

    HashMap();

    ~HashMap();

    bool isPresent(char* hashFactor);

    Vector<String>& getKeys();

    T* get(char* hashFactor);

    bool set(char* hashFactor, T value);

    void update(char* hashFactor, T value);

    void clear();

    size_t collisionCount();

    size_t getCount();

};
template<typename T>
HashMap<T>::HashMap(): count(), collisions(), buckets(new List<HashNode<T>>*[HashSize]) {}

template<typename T>
HashMap<T>::~HashMap() {

    for(size_t i = 0; i < HashSize; i++) {

        delete buckets[i];

    }

    delete[] buckets;
}

template<typename T>
void HashMap<T>::clear() {

    for(int i = 0; i < keys.size(); i++) {

        int index = this->hash(keys[i]);
        delete buckets[index];
        buckets[index] = nullptr;

    }

}

template<typename T>
const int HashMap<T>::HashSize = 100000;

//djb2 hashing by Dan Bernstein
template<typename T>
unsigned long HashMap<T>::hash(const char* hashVal) {

    unsigned long hash = 5381;
    int c;

    while((c = *hashVal++)) {

        hash = 33*hash + 77*hash + c;

    }

    return hash % HashSize;

}

template<typename T>
bool HashMap<T>::set(char* hashFactor, T value) {

    size_t index = hash(hashFactor);
    if(!buckets[index]) { buckets[index] = new List<HashNode<T>>; }
//    else { collisions++; }

    T* duplicateNode = get(hashFactor);

    if(!duplicateNode) {

        keys.pushBack(hashFactor);
        buckets[index]->pushBack(HashNode(std::move(value), hashFactor));
        count++;

    } else {

        update(hashFactor, std::move(value));

    }

    return true;

}

template<typename T>
void HashMap<T>::update(char *hashFactor, T value) {

    T* dest = get(hashFactor);
    *dest = value;

}

template<typename T>
T* HashMap<T>::get(char* hashFactor) {

    int index = hash(hashFactor);

    List<HashNode<T>>* bucket = buckets[index];
    if(!bucket) { return nullptr; }

    Node<HashNode<T>>* iter = bucket->getFirst();

    for(;iter; iter = iter->next) {

        if(iter->data.key == hashFactor) { return &iter->data.value; }

    }

    return nullptr;

}

template<typename T>
bool HashMap<T>::isPresent(char *hashFactor) {

    int index = hash(hashFactor);

    List<HashNode<T>> *bucket = buckets[index];
    if (!bucket) { return false; }

    Node<HashNode<T>> *iter = bucket->getFirst();

    for (; iter; iter = iter->next) {

        if (iter->data.key == hashFactor) { return true; }

    }

    return false;

}

template<typename T>
size_t HashMap<T>::collisionCount() { return collisions; }

template<typename T>
size_t HashMap<T>::getCount() { return count; }

template<typename T>
Vector<String>& HashMap<T>::getKeys() { return keys; }


