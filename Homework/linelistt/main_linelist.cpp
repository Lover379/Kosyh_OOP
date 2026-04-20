#include <iostream>
#include <iomanip>
#include <chrono>
#include "LineList.h"

using namespace std;

void solveJosephus(int N, int k) {
    if (N <= 0) return;

    // Начало замера (включая создание списка)
    auto start_t = chrono::high_resolution_clock::now();

    LineList<int> list;
    // Заполняем список: 1 будет в начале, N в конце
    for (int i = N; i >= 1; i--) list.insertFirst(i);

    int result = 0;
    if (N > 1) {
        list.makeCircular();

        // Устанавливаем prev на ПЕРВЫЙ элемент (число 1)
        // Тогда при k=2 следующим удалится ВТОРОЙ элемент (число 2)
        LineListElem<int>* prev = list.getStart();

        int remaining = N;
        while (remaining > 1) {
            if (k == 2) {
                // Удаляем элемент СЛЕДУЮЩИЙ за prev
                list.deleteAfter(prev);
                // Переходим к новому следующему
                prev = prev->getNext();
            }
            else {
                // Для k > 2 делаем k-1 переходов
                for (int i = 1; i < k; i++) prev = prev->getNext();
                list.deleteAfter(prev);
            }
            remaining--;
        }
        result = prev->getData();
    }
    else {
        result = 1;
    }

    auto end_t = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_t - start_t;

    cout << setw(10) << N << " | "
        << setw(10) << result << " | "
        << setw(15) << fixed << setprecision(6) << elapsed.count() << " sec" << endl;
}

int main() {
    int test_N[] = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int k = 2;

    cout << "------------------------------------------------------------" << endl;
    cout << setw(10) << "N" << " | " << setw(10) << "Result" << " | " << setw(15) << "Time (sec)" << endl;
    cout << "------------------------------------------------------------" << endl;

    for (int n : test_N) {
        solveJosephus(n, k);
    }
    cout << "------------------------------------------------------------" << endl;

    return 0;
}