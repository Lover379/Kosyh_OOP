#pragma once
#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <fstream>

template<typename T>
class Array {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize() ;

public:
    Array() : data(nullptr), size(0), capacity(0) {}

    explicit Array(size_t n) : size(n), capacity(n) ;

    ~Array()
    T& operator[](size_t index) ;

    size_t get_size() const ;

    void remove_at(size_t index) ;
};

int josephus(int N, int k) ;

double measure_time(int N, int k) ;

