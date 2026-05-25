#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Pro_lunu.h"

using namespace std;

void print_time(int hms) {
    int h = hms / 10000;
    int m = (hms / 100) % 100;
    int s = hms % 100;
    if (h < 10) cout << "0"; cout << h << ":";
    if (m < 10) cout << "0"; cout << m << ":";
    if (s < 10) cout << "0"; cout << s;
}

bool isValidDate(int d, int m, int y) {
    if (y < 1 || m < 1 || m > 12 || d < 1) return false;

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (m == 2) {
        bool isLeap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        if (isLeap) daysInMonth[2] = 29;
    }

    return d <= daysInMonth[m];
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int dd, mm, yyyy;
    char dot;
    cout << "Введите дату (дд.мм.гггг): ";

    if (!(cin >> dd >> dot >> mm >> dot >> yyyy) || dot != '.') {
        cout << "Данные некорректны" << endl;
        return 1;
    }

    if (!isValidDate(dd, mm, yyyy)) {
        cout << "Неверная дата" << endl;
        return 1;
    }

    char fname[32];
    sprintf(fname, "%04d%02d%02d.dat", yyyy, mm, dd);
    FILE* f = fopen(fname, "r");

    if (!f) {
        sprintf(fname, "moon%04d.dat", yyyy);
        f = fopen(fname, "r");
    }

    if (!f) {
        cout << "Файл не найден" << endl;
        return 1;
    }

    int rise = -1, set = -1, culm = -1;
    double max_el = -99.0;

    bool has_prev = false;
    int prev_ymd = -1;
    int prev_hms = -1;
    double prev_el = 0.0;
    bool dataFound = false;

    int targetYMD = yyyy * 10000 + mm * 100 + dd;
    int ymd, hms;
    double T, R, El, Az, FI, LG;
    char line[512];

    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        cout << "Данные некорректны" << endl;
        return 1;
    }

    while (fgets(line, sizeof(line), f)) {
        int current_ymd = atoi(line);
        if (current_ymd <= 0) continue;

        if (current_ymd < targetYMD) {
            if (targetYMD - current_ymd == 1 || current_ymd % 100 == 31 || current_ymd % 100 == 30) {
                if (sscanf(line, "%d %d %lf %lf %lf %lf %lf %lf", &ymd, &hms, &T, &R, &El, &Az, &FI, &LG) == 8) {
                    prev_ymd = ymd;
                    prev_hms = hms;
                    prev_el = El;
                    has_prev = true;
                }
            }
            continue;
        }

        if (current_ymd > targetYMD) {
            break;
        }

        if (sscanf(line, "%d %d %lf %lf %lf %lf %lf %lf", &ymd, &hms, &T, &R, &El, &Az, &FI, &LG) != 8) {
            continue;
        }

        dataFound = true;

        if (has_prev) {
            if (prev_el < 0 && El >= 0 && rise == -1) {
                rise = hms;
            }
            if (prev_el >= 0 && El < 0 && set == -1) {
                set = hms;
            }
        }

        if (El > max_el) {
            max_el = El;
            culm = hms;
        }

        prev_ymd = ymd;
        prev_hms = hms;
        prev_el = El;
        has_prev = true;
    }

    fclose(f);

    if (!dataFound) {
        cout << "Данные некорректны" << endl;
        return 1;
    }

    DateTime targetDate(dd, mm, yyyy);
    cout << "Дата: "; targetDate.showFormat1(); cout << "\n";
    cout << "Восход Луны: "; if (rise >= 0) print_time(rise); else cout << "---";
    cout << "\nКульминация Луны: "; if (culm >= 0) print_time(culm); else cout << "---";
    cout << "\nЗаход Луны: "; if (set >= 0) print_time(set); else cout << "---";
    cout << endl;

    return 0;
}
