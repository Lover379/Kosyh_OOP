#include <iostream>
#include <windows.h>
#include "graf.h"

using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    cout << "--- Тест I, II, III (Файл testgraph.txt) ---" << endl;
    Graf testGraf("testgraph.txt");

    cout << "Проверка BFS (путь от 0 до 28): " << (testGraf.runBFSTest(0, 28) ? "Есть" : "Нет") << endl;
    cout << "Проверка BFS (путь от 0 до 2): " << (testGraf.runBFSTest(0, 2) ? "Есть" : "Нет") << endl;

    cout << "\n--- Тестовая задача IV (Разделение testgraph.txt) ---" << endl;
    testGraf.saveComponents("testgraph.txt");
    cout << "Компоненты графа testgraph.txt сохранены." << endl;

    cout << "\n--- Основная задача V (Разделение 1000.csv) ---" << endl;
    Graf mainGraf("1000.csv");
    mainGraf.saveComponents("1000.csv");
    cout << "Компоненты графа 1000.csv сохранены." << endl;

    return 0;
}