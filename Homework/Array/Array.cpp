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

    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    Array() : data(nullptr), size(0), capacity(0) {}

    explicit Array(size_t n) : size(n), capacity(n) {
        data = new T[capacity];
    }

    ~Array() {
        delete[] data;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    size_t get_size() const {
        return size;
    }

    void remove_at(size_t index) {
        for (size_t i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
};

int josephus(int N, int k) {
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

double measure_time(int N, int k) {
    auto start = std::chrono::high_resolution_clock::now();
    josephus(N, k);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    std::ofstream file("josephus_results.csv");
    file << "N,Answer,Time_seconds\n";

    std::vector<int> values = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };

    for (int N : values) {
        double time = measure_time(N, 2);
        int answer = josephus(N, 2);

        file << N << "," << answer << "," << std::fixed << std::setprecision(6) << time << "\n";

        std::cout << "N=" << N << " Time=" << time << " sec Answer=" << answer << std::endl;
    }

    file.close();
    std::cout << "\nResults saved to josephus_results.csv" << std::endl;

    return 0;
}