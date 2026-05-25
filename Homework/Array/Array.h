#pragma once
#include <cstddef>

template<typename T>
class Array {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize();

public:
    Array() : data(nullptr), size(0), capacity(0) {}
    explicit Array(size_t n);
    ~Array();

    T& operator[](size_t index);
    size_t get_size() const;
    void remove_at(size_t index);
};

#include "array.cpp"