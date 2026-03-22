#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
using namespace std;

const int DEFAULT_CAPACITY = 10;

class ArrayException {};

class Array {
private:
    int* ptr;
    int size;
    int capacity;
    void increaseCapacity(int newCapacity);

public:
    explicit Array(int startCapacity = DEFAULT_CAPACITY);
    Array(const Array& arr);
    ~Array();

    void insert(int elem, int index);
    void insert(int elem);
    void remove(int index);

    int getSize() const;

    Array& operator=(const Array& arr);
    int& operator[](int index);

    friend ostream& operator<<(ostream& out, const Array& arr);
};

#endif