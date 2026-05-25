#define _CRT_SECURE_NO_WARNINGS
#include "datetime.h"
#include <iomanip>
#include <cmath>

using namespace std;

DateTime::DateTime() : dy(1), mn(1), yr(2000), hr(0), min(0), sec(0) {}

DateTime::DateTime(int d, int m, int y, int hh, int mm, int ss) 
    : dy(d), mn(m), yr(y), hr(hh), min(mm), sec(ss) {}

bool DateTime::leapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int DateTime::monthDays(int m, int y) const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && leapYear(y)) return 29;
    return days[m - 1];
}

bool DateTime::checkDate(int d, int m, int y) const {
    if (y < 1 || m < 1 || m > 12 || d < 1) return false;
    return d <= monthDays(m, y);
}

void DateTime::inputDate() {
    char dot;
    while (true) {
        cout << "Введите дату (дд.мм.гггг): ";
        if (cin >> dy >> dot >> mn >> dot >> yr && checkDate(dy, mn, yr)) {
            hr = min = sec = 0;
            break;
        }
        cout << "Ошибка: неверный формат или дата!" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void DateTime::showFormat1() const {
    cout << setfill('0') << setw(2) << dy << "."
         << setw(2) << mn << "." << yr << " ";
}

void DateTime::showFormat2() const {
    cout << yr << "/" << setw(2) << mn << "/" << setw(2) << dy << " ";
}

void DateTime::showFormat3() const {
    const char* months[] = { "Янв", "Фев", "Мар", "Апр", "Май", "Июн", "Июл", "Авг", "Сен", "Окт", "Ноя", "Дек" };
    cout << dy << " " << months[mn - 1] << " " << yr << " ";
}

void DateTime::showISO() const {
    cout << yr << "-" << setfill('0') << setw(2) << mn << "-" << setw(2) << dy;
}

const char* DateTime::weekDay() const {
    int q = dy;
    int m = mn;
    int y = yr;
    if (m < 3) {
        m += 12;
        y--;
    }
    int k = y % 100;
    int j = y / 100;
    int h = (q + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    
    const char* days[] = { "Суббота", "Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница" };
    return days[h];
}

long long DateTime::totalDays() const {
    long long total = dy;
    for (int y = 1; y < yr; ++y) {
        total += (leapYear(y) ? 366 : 365);
    }
    for (int m = 1; m < mn; ++m) {
        total += monthDays(m, yr);
    }
    return total;
}

long long DateTime::daysBetween(const DateTime& other) const {
    return llabs(this->totalDays() - other.totalDays());
}

DateTime DateTime::catholikEaster(int y) {
    int a = y % 19;
    int b = y / 100;
    int c = y % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int L = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * L) / 451;
    int month = (h + L - 7 * m + 114) / 31;
    int day = ((h + L - 7 * m + 114) % 31) + 1;
    return DateTime(day, month, y);
}

DateTime DateTime::orthodoxEaster(int y) {
    int a = y % 19;
    int b = y % 4;
    int c = y % 7;
    int d = (19 * a + 15) % 30;
    int e = (2 * b + 4 * c + 6 * d + 6) % 7;
    int f = d + e;
    
    int day, month;
    if (f <= 9) {
        day = 22 + f;
        month = 3;
    } else {
        day = f - 9;
        month = 4;
    }
    
    day += 13;
    int daysInApril = 30;
    if (month == 3 && day > 31) {
        day -= 31;
        month = 4;
    } else if (month == 4 && day > daysInApril) {
        day -= daysInApril;
        month = 5;
    }
    
    return DateTime(day, month, y);
}
