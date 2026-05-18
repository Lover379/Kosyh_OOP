#include "Array.h"

    Array::void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }


    Array() : data(nullptr), size(0), capacity(0) {}

    Array::explicit Array(size_t n) : size(n), capacity(n) {
        data = new T[capacity];
    }

    Array::~Array() {
        delete[] data;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    Array::size_t get_size() const {
        return size;
    }

    Array::void remove_at(size_t index) {
        for (size_t i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }


Array::int josephus(int N, int k) {
    if (N <= 0) return 0;

    Array<int> arr(N);
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    size_t index = 0;

    while (arr.get_size() > 1) {
        index = (index + k - 1) % arr.get_size();
        arr.remove_at(index);
    }

    return arr[0];
}

Array::double measure_time(int N, int k) {
    auto start = std::chrono::high_resolution_clock::now();
    josephus(N, k);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

