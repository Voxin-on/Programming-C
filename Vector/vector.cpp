#include "vector.h"

#include <iostream>
using namespace std;

Array::Array(int startCapacity) {
    capacity = (startCapacity <= 0) ? DEFAULT_CAPACITY : startCapacity;
    ptr = new int[capacity];
    size = 0;
}

Array::Array(const Array& arr) {
    capacity = arr.capacity;
    size = arr.size;
    ptr = new int[capacity];
    for (int i = 0; i < size; i++) ptr[i] = arr.ptr[i];
}

Array::~Array() {
    delete[] ptr;
}



void Array::increaseCapacity(int newCapacity) {
    int target = (newCapacity < capacity * 2) ? capacity * 2 : newCapacity;
    int* newPtr = new int[target];
    for (int i = 0; i < size; i++) newPtr[i] = ptr[i];
    delete[] ptr;
    ptr = newPtr;
    capacity = target;
}



void Array::insert(int elem, int index) {
    if (index < 0 || index > size) throw ArrayException();
    if (size == capacity) increaseCapacity(size + 1);
    
    for (int j = size; j > index; j--) ptr[j] = ptr[j - 1];
    ptr[index] = elem;
    size++;
}

void Array::insert(int elem) { insert(elem, size); }

void Array::remove(int index) {
    if (index < 0 || index >= size) throw ArrayException();
    for (int j = index; j < size - 1; j++) ptr[j] = ptr[j + 1];
    size--;
}



int& Array::operator[](int index) {
    if (index < 0 || index >= size) throw ArrayException();
    return ptr[index];
}

Array& Array::operator=(const Array& arr) {
    if (this == &arr) return *this;
    if (capacity != arr.capacity) {
        delete[] ptr;
        ptr = new int[arr.capacity];
        capacity = arr.capacity;
    }
    size = arr.size;
    for (int i = 0; i < size; i++) ptr[i] = arr.ptr[i];
    return *this;
}



int Array::getSize() const { 
    return size; 
}



ostream& operator <<(ostream& out, const Array& arr) {
    out<<"Total size: "<<arr.size<<endl;
    for (int i=0; i<arr.size; i++)
        out<<arr.ptr[i]<<endl;
    return out;
}