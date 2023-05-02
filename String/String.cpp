#include "String.h"
#include <cstdio>

const int String::BaseBufferSize = 8;

String::String() : buffer(nullptr), size() {}

String::String(const String &other) : size(other.size) {

    buffer = new char[other.size + 1];

    for(size_t i = 0; i < other.size; i++) { buffer[i] = other.buffer[i]; }

    buffer[other.size] = '\0';

}

String::operator char *() const { return buffer; }

String::String(String &&other) : size(other.size), buffer(nullptr) {

    std::swap(this->buffer, other.buffer);
    other.size = 0;

}

String::String(const char *str) {

    size_t newSize = 0;

    const char* checkSize = str;
    while(*checkSize++ != '\0') { newSize++; }

    buffer = new char[newSize + 1];
    this->size = newSize;

    for(size_t i = 0; i < newSize; i++) { buffer[i] = str[i]; }

    buffer[newSize] = '\0';

}

String::String(size_t len) {

    buffer = new char[len];
    size = len;

}

String::~String() {

    clear();

}

bool String::operator==(const char *other) const {

    if(!buffer || !other) { return false;}
    const char* thisStr = buffer;

    size_t i = 0;
    for(; *other ; i++) {

        if(i > size || *other++ != *thisStr++) { return false; }

    }

    if(i != size) { return false; }

    return true;

}

bool String::operator!=(const char *other) const {

    return !(*this == other);

}

bool String::operator==(const String &other) const {

    if(size != other.size) return false;

    const char* otherStr = other.buffer;

    return *this == otherStr;

}

String &String::operator+=(const char *other) {

    String str(other);
    *this += str;

    return *this;
}

String &String::operator+=(const String &other) {

    size_t newSize = other.size + size;

    String tmpOther(other);
    String tmpThis(*this);

    delete[] buffer;
    buffer = new char[newSize + 1];
    for(size_t i = 0; i < size; i++) { buffer[i] = tmpThis[i]; }
    for(size_t i = 0; i < other.size; i++) { buffer[i + size] = tmpOther[i]; }

    buffer[newSize] = '\0';
    size = newSize;

    return *this;

}

String &String::operator=(const char *other) {

    if(!other) { return *this; }

    size_t newSize = 0;
    for(; *(other+newSize); newSize++) {}

    clear();

    buffer = new char[newSize + 1];
    size = newSize;

    for(size_t i = 0; i < newSize; i++) { buffer[i] = other[i]; }

    buffer[newSize] = '\0';

    return *this;

}

String &String::operator=(const String &other) {

    if(this == &other) { return *this; }

    *this = (const char*) other.buffer;

    return *this;
}

void String::clear() {

    size = 0;
    delete[] buffer;
    buffer = nullptr;

}

size_t String::length() const { return size; }

 char& String::operator[](size_t index) { return buffer[index]; }
//
char String::operator[](size_t index) const { return buffer[index]; }

std::ostream& operator<<(std::ostream& out, const String& str) {

    for(size_t i = 0; i < str.size; i++) { out << str.buffer[i]; }

    return out;
}

void String::read() {

    unsigned int tail = 0;
    int next;

    while((next = getchar_unlocked()) <= 32);

    ungetc(next, stdin);

    while ((next = getchar_unlocked())) {

        if(next <= 32) break;

        buffer[tail++] = next;

    }

    buffer[tail] = '\0';
    size = tail;

}

std::istream& operator>>(std::istream& in, String& str) {

    str.clear();

    std::istream::sentry sentry(in);

    unsigned int size = String::BaseBufferSize;
    unsigned int tail = 0;
    char* temp = new char[size + 1];
    int next;

    while ((next = in.peek()) && next != -1 && std::cin.peek() != '=') {

        if(std::isspace(next) || next == '\n') {in.get(); break; }

        if (tail >= size) {

            unsigned int newsize = std::max(2*size, 16u);
            char* newtemp = new char[newsize+1];
            for(int i = 0; i < size; i++) { newtemp[i] = temp[i]; }
            newtemp[newsize] = '\0';
            delete [] temp;
            temp = newtemp;
            size = newsize;

        }

        temp[tail++] = in.get();

    }

    temp[tail] = '\0';
    str.buffer = temp;
    str.size = tail;

    return in;
}

String &String::operator=(const char other) {
//
//    String newString = "";
//    newString = other;
//    *this = newString;
//
//    return *this;

}

