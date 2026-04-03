#include <iostream>
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

    cout << "\n=== Дата Пасхи ===\n";
    int yrs[] = { 2022, 2023, 2024, 2025 };
    for (int idx = 0; idx < 4; idx++)
    {
        cout << yrs[idx] << " | Католическая: ";
        DateTime::catholikEaster(yrs[idx]).showFormat2();
        cout << "       Православная: ";
        DateTime::orthodoxEaster(yrs[idx]).showFormat2();
    }

    cout << "\n=== Ввод с клавиатуры ===\n";
    DateTime dt3;
    dt3.inputDate();
    cout << "Вы ввели: ";
    dt3.showFormat2();
    cout << "ISO: ";
    dt3.showISO();
    cout << "День недели: " << dt3.weekDay() << "\n";

    return 0;
}