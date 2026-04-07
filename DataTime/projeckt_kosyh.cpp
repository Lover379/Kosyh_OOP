#include "datetime.h"
#include <iomanip>
using namespace std;

bool DateTime::leapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int DateTime::monthDays(int m, int y) const {
    int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && leapYear(y)) return 29;
    return days[m - 1];
}

long long DateTime::totalDays() const {
    int yVar = yr - (mn <= 2);
    long long total = yr * 365LL + dy;
    for (int i = 1; i < mn; i++) total += monthDays(i, yr);
    total += yVar / 4 - yVar / 100 + yVar / 400;
    return total;
}

DateTime::DateTime() : dy(1), mn(1), yr(2000), hr(0), min(0), sec(0) {}

DateTime::DateTime(int d, int m, int y, int hh, int mm, int ss) {
    if (checkDate(d, m, y)) { dy = d; mn = m; yr = y; hr = hh; min = mm; sec = ss; }
    else { cout << "Некорректная дата! Установлено 01.01.2000\n"; *this = DateTime(); }
}

bool DateTime::checkDate(int d, int m, int y) const {
    if (y < 1 || m < 1 || m>12 || d < 1) return false;
    return d <= monthDays(m, y);
}

void DateTime::validateAndFix() {
    if (sec >= 60) { min += sec / 60; sec %= 60; }
    if (sec < 0) sec = 0;
    if (min >= 60) { hr += min / 60; min %= 60; }
    if (min < 0) min = 0;
    if (hr >= 24) { dy += hr / 24; hr %= 24; }
    if (hr < 0) hr = 0;

    while (dy > monthDays(mn, yr)) {
        dy -= monthDays(mn, yr);
        if (++mn > 12) { mn = 1; yr++; }
    }
    while (dy < 1) {
        if (--mn < 1) { mn = 12; yr--; }
        dy += monthDays(mn, yr);
    }
    if (mn < 1) mn = 1;
    if (mn > 12) { yr += (mn - 1) / 12; mn = ((mn - 1) % 12) + 1; }
}

void DateTime::inputDate() {
    int d, m, y, hh, mm, ss;
    cout << "Введите дату (день месяц год): "; cin >> d >> m >> y;
    cout << "Введите время (час минута секунда): "; cin >> hh >> mm >> ss;
    if (checkDate(d, m, y)) {
        dy = d; mn = m; yr = y; hr = hh; min = mm; sec = ss;
        validateAndFix();
        cout << "Дата успешно обновлена.\n";
    }
    else cout << "Ошибка: некорректная дата!\n";
}

void DateTime::showFormat1() const {
    cout << dy << "." << (mn < 10 ? "0" : "") << mn << "." << yr << "\n";
}

void DateTime::showFormat2() const {
    const char* names[] = { "","января","февраля","марта","апреля","мая","июня",
                         "июля","августа","сентября","октября","ноября","декабря" };
    cout << dy << " " << names[mn] << " " << yr << "\n";
}

void DateTime::showFormat3() const {
    cout << (dy < 10 ? "0" : "") << dy << "." << (mn < 10 ? "0" : "") << mn << "."
        << (yr % 100 < 10 ? "0" : "") << yr % 100 << "\n";
}

void DateTime::showISO() const {
    cout << setw(4) << setfill('0') << yr << "-" << setw(2) << setfill('0') << mn << "-"
        << setw(2) << setfill('0') << dy << "T" << setw(2) << setfill('0') << hr << ":"
        << setw(2) << setfill('0') << min << ":" << setw(2) << setfill('0') << sec << "\n";
}

long long DateTime::daysBetween(const DateTime& other) const {
    long long diff = totalDays() - other.totalDays();
    return diff < 0 ? -diff : diff;
}

const char* DateTime::weekDay() const {
    int d = dy, m = mn, y = yr;
    if (m < 3) { m += 12; y--; }
    int k = y % 100, j = y / 100;
    int w = (d + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
    if (w < 0) w += 7;
    const char* days[] = { "Суббота","Воскресенье","Понедельник","Вторник",
                        "Среда","Четверг","Пятница" };
    return days[w];
}

bool DateTime::operator==(const DateTime& o) const {
    return yr == o.yr && mn == o.mn && dy == o.dy && hr == o.hr && min == o.min && sec == o.sec;
}
bool DateTime::operator!=(const DateTime& o) const { return !(*this == o); }
bool DateTime::operator<(const DateTime& o) const {
    if (yr != o.yr) return yr < o.yr;
    if (mn != o.mn) return mn < o.mn;
    if (dy != o.dy) return dy < o.dy;
    if (hr != o.hr) return hr < o.hr;
    if (min != o.min) return min < o.min;
    return sec < o.sec;
}
bool DateTime::operator>(const DateTime& o) const { return o < *this; }
bool DateTime::operator<=(const DateTime& o) const { return !(*this > o); }
bool DateTime::operator>=(const DateTime& o) const { return !(*this < o); }

DateTime DateTime::operator+(int days) const {
    DateTime r = *this;
    r.dy += days;
    r.validateAndFix();
    return r;
}
DateTime DateTime::operator-(int days) const {
    DateTime r = *this;
    r.dy -= days;
    r.validateAndFix();
    return r;
}
int DateTime::operator-(const DateTime& o) const { return (int)daysBetween(o); }

ostream& operator<<(ostream& os, const DateTime& dt) {
    os << dt.dy << "." << dt.mn << "." << dt.yr << " "
        << (dt.hr < 10 ? "0" : "") << dt.hr << ":" << (dt.min < 10 ? "0" : "") << dt.min << ":"
        << (dt.sec < 10 ? "0" : "") << dt.sec;
    return os;
}

istream& operator>>(istream& is, DateTime& dt) {
    int d, m, y, hh, mm, ss;
    cout << "Введите дату (день месяц год): "; is >> d >> m >> y;
    cout << "Введите время (час минута секунда): "; is >> hh >> mm >> ss;
    if (dt.checkDate(d, m, y)) {
        dt.dy = d; dt.mn = m; dt.yr = y; dt.hr = hh; dt.min = mm; dt.sec = ss;
        dt.validateAndFix();
    }
    else { cout << "Ошибка! Установлена текущая.\n"; dt = DateTime(); }
    return is;
}

DateTime DateTime::catholikEaster(int y) {
    int a = y % 19, b = y / 100, c = y % 100, d = b / 4, e = b % 4, f = (b + 8) / 25, g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30, i = c / 4, k = c % 4, l = (32 + 2 * e + 2 * i - h - k) % 7;
    int mE = (a + 11 * h + 22 * l) / 451, mo = (h + l - 7 * mE + 114) / 31, da = (h + l - 7 * mE + 114) % 31 + 1;
    return DateTime(da, mo, y);
}

DateTime DateTime::orthodoxEaster(int y) {
    int a = y % 4, b = y % 7, c = y % 19, d = (19 * c + 15) % 30, e = (2 * a + 4 * b - d + 34) % 7;
    int mo = (d + e + 114) / 31, da = (d + e + 114) % 31 + 1 + 13;
    if (da > 30 && mo == 4) { da -= 30; mo = 5; }
    if (da > 31 && mo == 5) { da -= 31; mo = 6; }
    return DateTime(da, mo, y);
}
