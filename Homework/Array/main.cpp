#include "array.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>

int josephus(int N, int k) {
    if (N <= 0) return 0;

    Array<int> arr(1);

    int lucky_position = 0;
    for (int i = 1; i <= N; ++i) {
        lucky_position = (lucky_position + k) % i;
    }

    arr[0] = lucky_position + 1;
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
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Заголовок таблицы из 3 столбцов
    file << "N,Answer,Time_seconds\n";

    std::vector<int> values = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int k = 2;

    std::cout << std::setw(10) << "N" << std::setw(12) << "Answer" << std::setw(18) << "Time (sec)" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    for (int N : values) {
        auto start = std::chrono::high_resolution_clock::now();
        int answer = josephus(N, k);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        double time = duration.count();

        // Запись ровно в 3 столбца, разделенных запятыми для формата CSV
        file << N << "," << answer << "," << std::fixed << std::setprecision(6) << time << "\n";

        std::cout << std::setw(10) << N
            << std::setw(12) << answer
            << std::setw(18) << std::fixed << std::setprecision(6) << time
            << std::endl;
    }

    file.close();
    std::cout << "\nResults saved to josephus_results.csv" << std::endl;

    return 0;
}