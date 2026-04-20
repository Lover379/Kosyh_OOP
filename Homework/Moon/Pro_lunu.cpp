#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include "datetime.h"

using namespace std;

void print_time(int hms) {
    int h = hms / 10000;
    int m = (hms / 100) % 100;
    int s = hms % 100;
    if (h < 10) cout << "0"; cout << h << ":";
    if (m < 10) cout << "0"; cout << m << ":";
    if (s < 10) cout << "0"; cout << s;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int dd, mm, yyyy;
    char dot;
    cout << "Введите дату (дд.мм.гггг): ";

    if (!(cin >> dd >> dot >> mm >> dot >> yyyy)) return 1;

    DateTime targetDate(dd, mm, yyyy);
    if (!targetDate.checkDate(dd, mm, yyyy)) {
        cout << "Ошибка: неверная дата" << endl;
        return 1;
    }

    char fname[20];
    sprintf(fname, "moon%04d.dat", yyyy);

    FILE* f = fopen(fname, "r");
    if (!f) {
        cout << "Файл не найден" << endl;
        return 1;
    }

    char header[256];
    fgets(header, sizeof(header), f);

    int rise = -1, set = -1, culm = -1;
    double max_el = -99, prev_el = 99;
    int prev_hms = -1, targetYMD = yyyy * 10000 + mm * 100 + dd;

    int ymd, hms;
    double T, R, El, Az, FI, LG;

    while (fscanf(f, "%d %d %lf %lf %lf %lf %lf %lf", &ymd, &hms, &T, &R, &El, &Az, &FI, &LG) == 8) {
        if (ymd != targetYMD) {
            if (prev_hms != -1 && ymd > targetYMD) break;
            prev_el = 99; prev_hms = -1;
            continue;
        }

        if (prev_hms != -1) {
            if (prev_el < 0 && El >= 0 && rise == -1) {
                double ratio = -prev_el / (El - prev_el);
                int p = (prev_hms / 10000) * 3600 + ((prev_hms / 100) % 100) * 60 + (prev_hms % 100);
                int c = (hms / 10000) * 3600 + ((hms / 100) % 100) * 60 + (hms % 100);
                int r = p + (int)(ratio * (c - p) + 0.5);
                rise = (r / 3600) * 10000 + ((r % 3600) / 60) * 100 + (r % 60);
            }
            if (prev_el >= 0 && El < 0 && set == -1) {
                double ratio = prev_el / (prev_el - El);
                int p = (prev_hms / 10000) * 3600 + ((prev_hms / 100) % 100) * 60 + (prev_hms % 100);
                int c = (hms / 10000) * 3600 + ((hms / 100) % 100) * 60 + (hms % 100);
                int s = p + (int)(ratio * (c - p) + 0.5);
                set = (s / 3600) * 10000 + ((s % 3600) / 60) * 100 + (s % 60);
            }
        }

        if (El > max_el) { max_el = El; culm = hms; }
        prev_el = El; prev_hms = hms;
    }
    fclose(f);

    if (prev_hms == -1) { cout << "Данные не найдены" << endl; return 1; }

    cout << "Дата: "; targetDate.showFormat1();
    cout << "День недели: " << targetDate.weekDay() << endl;
    cout << "Восход: "; if (rise >= 0) print_time(rise); else cout << "---";
    cout << "\nКульминация: "; if (culm >= 0) print_time(culm); else cout << "---";
    cout << "\nЗаход: "; if (set >= 0) print_time(set); else cout << "---";
    cout << endl;

    return 0;
}
