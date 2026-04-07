#include <iostream>
#include <clocale>
#include "datetime.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, ".UTF8");

    cout << "=== Форматы вывода ===\n";
    DateTime dt1(17, 3, 2025, 9, 15, 0);
    dt1.showFormat1();
    dt1.showFormat2();
    dt1.showFormat3();
    dt1.showISO();
    cout << "День недели: " << dt1.weekDay() << "\n";

    cout << "\n=== Разница дат ===\n";
    DateTime dt2(4, 11, 2025);
    cout << "Разница: " << dt1.daysBetween(dt2) << " дн.\n";

    cout << "\n=== Проверка корректности ===\n";
    DateTime d1(28, 2, 2025);
    cout << "28.02.2025: ";
    d1.showFormat1();
    DateTime d2(29, 2, 2025);

    cout << "\n=== Проверка валидности дат ===\n";
    int testDates[][3] = { {31, 4, 2025}, {29, 2, 2024}, {29, 2, 2025}, {0, 1, 2025}, {1, 13, 2025} };
    for (int i = 0; i < 5; i++)
    {
        cout << testDates[i][0] << "." << testDates[i][1] << "." << testDates[i][2] << " - ";
        if (d1.checkDate(testDates[i][0], testDates[i][1], testDates[i][2]))
            cout << "корректная\n";
        else
            cout << "некорректная\n";
    }

    cout << "\n=== Дата Пасхи ===\n";
    int yrs[] = { 2022, 2023, 2024, 2025 };
    for (int idx = 0; idx < 4; idx++)
    {
        cout << yrs[idx] << " | Католическая: ";
        DateTime::catholikEaster(yrs[idx]).showFormat2();
        cout << "       Православная: ";
        DateTime::orthodoxEaster(yrs[idx]).showFormat2();
    }

    cout << "\n=== Демонстрация перегрузки операторов ===\n";
    DateTime dt3(28, 2, 2025);
    DateTime dt4(1, 3, 2025);

    cout << "dt3 = " << dt3 << endl;
    cout << "dt4 = " << dt4 << endl;

    cout << "dt3 == dt4: " << (dt3 == dt4 ? "true" : "false") << endl;
    cout << "dt3 < dt4: " << (dt3 < dt4 ? "true" : "false") << endl;
    cout << "dt3 > dt4: " << (dt3 > dt4 ? "true" : "false") << endl;

    DateTime dt5 = dt3 + 5;
    cout << "dt3 + 5 дней = " << dt5 << endl;

    DateTime dt6 = dt4 - 3;
    cout << "dt4 - 3 дня = " << dt6 << endl;

    int diff = dt4 - dt3;
    cout << "Разница между dt4 и dt3: " << diff << " дней" << endl;

    cout << "\n=== Увеличение/уменьшение ===\n";
    DateTime dt7(31, 12, 2025);
    cout << "Исходная дата: " << dt7 << endl;
    dt7 = dt7 + 1;
    cout << "После +1 день: " << dt7 << endl;
    dt7 = dt7 + 1;
    cout << "После ещё +1 день: " << dt7 << endl;
    dt7 = dt7 - 1;
    cout << "После -1 день: " << dt7 << endl;
    dt7 = dt7 - 1;
    cout << "После ещё -1 день: " << dt7 << endl;

    cout << "\n=== Ввод с клавиатуры (через перегруженный оператор >>) ===\n";
    DateTime dt8;
    cin >> dt8;
    cout << "Вы ввели: " << dt8 << endl;
    cout << "ISO: ";
    dt8.showISO();
    cout << "День недели: " << dt8.weekDay() << "\n";

    return 0;
}
