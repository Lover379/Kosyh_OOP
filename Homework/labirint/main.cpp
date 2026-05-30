#include <iostream>
#include "labirint.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    string inputFile = "ДНК_Лабиринт.bmp";
    string outputFile = "ДНК_Лабиринт_решение.bmp";

    Labyrinth lab;

    if (!lab.loadBMP(inputFile)) {
        return 1;
    }

    cout << "Поиск оптимального пути алгоритмом Ли..." << endl;
    if (!lab.solve()) {
        return 1;
    }

    cout << "Сохранение изображения с найденным путем..." << endl;
    if (!lab.saveBMP(outputFile)) {
        return 1;
    }

    cout << "Успех! Результат сохранен в файл: " << outputFile << endl;
    return 0;
}