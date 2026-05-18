#include 'Array.h'
#include iostream

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