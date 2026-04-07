#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <windows.h>

void print_time(int hms) {
    int h = hms / 10000;
    int m = (hms / 100) % 100;
    int s = hms % 100;
    printf("%02d:%02d:%02d", h, m, s);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    char date_str[32];
    printf("Введите дату (дд.мм.гггг): ");
    scanf("%31s", date_str);

    int dd, mm, yyyy;
    sscanf(date_str, "%d.%d.%d", &dd, &mm, &yyyy);

    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0))
        days[1] = 29;

    if (yyyy < 1900 || yyyy > 2100 || mm < 1 || mm > 12 || dd < 1 || dd > days[mm - 1]) {
        printf("Ошибка: неверная дата\n");
        return 1;
    }

    int target = yyyy * 10000 + mm * 100 + dd;

    char fname[64];
    sprintf(fname, "moon%04d.dat", yyyy);

    FILE* f = fopen(fname, "r");
    if (!f) {
        printf("Ошибка: файл %s не найден\n", fname);
        return 1;
    }

    char line[256];
    fgets(line, sizeof(line), f);

    int rise = -1, set = -1, culm = -1;
    double max_el = -999;
    double prev_el = 999;
    int prev_hms = -1;
    int found = 0;

    int ymd, hms;
    double T, R, El, Az, FI, LG;

    while (fscanf(f, "%d %d %lf %lf %lf %lf %lf %lf", &ymd, &hms, &T, &R, &El, &Az, &FI, &LG) == 8) {
        if (ymd != target) {
            if (found) break;
            prev_el = 999;
            prev_hms = -1;
            continue;
        }
        found = 1;

        if (prev_hms != -1 && prev_el < 0 && El >= 0 && rise == -1) {
            double ratio = -prev_el / (El - prev_el);
            int p = (prev_hms / 10000) * 3600 + ((prev_hms / 100) % 100) * 60 + (prev_hms % 100);
            int c = (hms / 10000) * 3600 + ((hms / 100) % 100) * 60 + (hms % 100);
            int r = p + (int)(ratio * (c - p) + 0.5);
            rise = (r / 3600) * 10000 + ((r % 3600) / 60) * 100 + (r % 60);
        }

        if (El > max_el) {
            max_el = El;
            culm = hms;
        }

        if (prev_hms != -1 && prev_el >= 0 && El < 0) {
            double ratio = prev_el / (prev_el - El);
            int p = (prev_hms / 10000) * 3600 + ((prev_hms / 100) % 100) * 60 + (prev_hms % 100);
            int c = (hms / 10000) * 3600 + ((hms / 100) % 100) * 60 + (hms % 100);
            int s = p + (int)(ratio * (c - p) + 0.5);
            set = (s / 3600) * 10000 + ((s % 3600) / 60) * 100 + (s % 60);
        }

        prev_el = El;
        prev_hms = hms;
    }

    fclose(f);

    if (!found) {
        printf("Ошибка: дата не найдена\n");
        return 1;
    }

    printf("Дата: %02d.%02d.%04d\n", dd, mm, yyyy);

    printf("Восход: ");
    if (rise >= 0) print_time(rise); else printf("---");

    printf("\nКульминация: ");
    if (culm >= 0) print_time(culm); else printf("---");

    printf("\nЗаход: ");
    if (set >= 0) print_time(set); else printf("---");

    printf("\n");
    return 0;
}