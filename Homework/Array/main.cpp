#include "Array.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <chrono>

int main() {
    std::ofstream file("josephus_results.csv");
    file << "N,Answer,Time_seconds\n";

    std::vector<int> values = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };

    for (int N : values) {
        auto start = std::chrono::high_resolution_clock::now();
        
        int answer = josephus(N, 2);
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        double time = duration.count();

        file << N << "," << answer << "," << std::fixed << std::setprecision(6) << time << "\n";

        std::cout << "N=" << N << " Time=" << time << " sec Answer=" << answer << std::endl;
    }

    file.close();
    std::cout << "\nResults saved to josephus_results.csv" << std::endl;

    return 0;
}
