#ifndef ARRAY_CPP
#define ARRAY_CPP

#include "array.h"
#include <stdexcept>

template<typename T>
Array<T>::Array(size_t n) : size(n), capacity(n) {
    data = new T[capacity];
}

template<typename T>
Array<T>::~Array() {
    delete[] data;
}

template<typename T>
void Array<T>::resize() {
    capacity = (capacity == 0) ? 1 : capacity * 2;
    T* newData = new T[capacity];
    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

template<typename T>
T& Array<T>::operator[](size_t index) {
    return data[index];
}

template<typename T>
size_t Array<T>::get_size() const {
    return size;
}

template<typename T>
void Array<T>::remove_at(size_t index) {
    for (size_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

#endif