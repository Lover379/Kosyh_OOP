#include "datetime.h"

using namespace std;

bool DateTime::leapYear(int y) const
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int DateTime::monthDays(int m, int y) const
{
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && leapYear(y))
        return 29;
    return daysInMonth[m];
}

long long DateTime::totalDays() const
{
    int yVar = yr;
    if (mn <= 2)
        yVar--;
    long long total = yr * 365LL + dy;
    for (int i = 1; i < mn; i++)
        total += monthDays(i, yr);
    total += (yVar / 4 - yVar / 100 + yVar / 400);
    return total;
}

DateTime::DateTime()
{
    dy = 1;
    mn = 1;
    yr = 2000;
    hr = 0;
    min = 0;
    sec = 0;
}

DateTime::DateTime(int d, int m, int y, int hh, int mm, int ss)
{
    if (checkDate(d, m, y))
    {
        dy = d;
        mn = m;
        yr = y;
        hr = hh;
        min = mm;
        sec = ss;
    }
    else
    {
        cout << "Некорректная дата! Установлено 01.01.2000\n";
        dy = 1;
        mn = 1;
        yr = 2000;
        hr = 0;
        min = 0;
        sec = 0;
    }
}

bool DateTime::checkDate(int d, int m, int y) const
{
    if (y < 1 || m < 1 || m > 12 || d < 1)
        return false;
    return d <= monthDays(m, y);
}

void DateTime::inputDate()
{
    int d, m, y, hh, mm, ss;
    cout << "Введите дату (день месяц год): ";
    cin >> d >> m >> y;
    cout << "Введите время (час минута секунда): ";
    cin >> hh >> mm >> ss;
    if (checkDate(d, m, y))
    {
        dy = d;
        mn = m;
        yr = y;
        hr = hh;
        min = mm;
        sec = ss;
        cout << "Дата успешно обновлена.\n";
    }
    else
    {
        cout << "Ошибка: некорректная дата!\n";
    }
}

void DateTime::showFormat1() const
{
    cout << dy << ".";
    if (mn < 10)
        cout << "0";
    cout << mn << "." << yr << "\n";
}

void DateTime::showFormat2() const
{
    const char* monthNames[] = { "", "января", "февраля", "марта", "апреля", "мая", "июня",
                                "июля", "августа", "сентября", "октября", "ноября", "декабря" };
    cout << dy << " " << monthNames[mn] << " " << yr << "\n";
}

void DateTime::showFormat3() const
{
    if (dy < 10)
        cout << "0";
    cout << dy << ".";
    if (mn < 10)
        cout << "0";
    cout << mn << ".";
    int shortYear = yr % 100;
    if (shortYear < 10)
        cout << "0";
    cout << shortYear << "\n";
}

void DateTime::showISO() const
{
    if (yr < 1000)
        cout << "0";
    if (yr < 100)
        cout << "0";
    if (yr < 10)
        cout << "0";
    cout << yr << "-";
    if (mn < 10)
        cout << "0";
    cout << mn << "-";
    if (dy < 10)
        cout << "0";
    cout << dy << "T";
    if (hr < 10)
        cout << "0";
    cout << hr << ":";
    if (min < 10)
        cout << "0";
    cout << min << ":";
    if (sec < 10)
        cout << "0";
    cout << sec << "\n";
}

long long DateTime::daysBetween(const DateTime& other) const
{
    long long difference = totalDays() - other.totalDays();
    return difference < 0 ? -difference : difference;
}

const char* DateTime::weekDay() const
{
    int dVal = dy, mVal = mn, yVal = yr;
    if (mVal < 3)
    {
        mVal += 12;
        yVal--;
    }
    int kVal = yVal % 100, jVal = yVal / 100;
    int weekdayNum = (dVal + (13 * (mVal + 1)) / 5 + kVal + kVal / 4 + jVal / 4 - 2 * jVal) % 7;
    if (weekdayNum < 0)
        weekdayNum += 7;
    const char* weekdays[] = { "Суббота", "Воскресенье", "Понедельник", "Вторник",
                              "Среда", "Четверг", "Пятница" };
    return weekdays[weekdayNum];
}

DateTime DateTime::catholikEaster(int y)
{
    int aVar = y % 19, bVar = y / 100, cVar = y % 100;
    int dVar = bVar / 4, eVar = bVar % 4, fVar = (bVar + 8) / 25;
    int gVar = (bVar - fVar + 1) / 3;
    int hVar = (19 * aVar + bVar - dVar - gVar + 15) % 30;
    int iVar = cVar / 4, kVar = cVar % 4;
    int lVar = (32 + 2 * eVar + 2 * iVar - hVar - kVar) % 7;
    int mnVar = (aVar + 11 * hVar + 22 * lVar) / 451;
    int moVar = (hVar + lVar - 7 * mnVar + 114) / 31;
    int daVar = (hVar + lVar - 7 * mnVar + 114) % 31 + 1;
    return DateTime(daVar, moVar, y);
}

DateTime DateTime::orthodoxEaster(int y)
{
    int aVal = y % 4, bVal = y % 7, cVal = y % 19;
    int dVal = (19 * cVal + 15) % 30;
    int eVal = (2 * aVal + 4 * bVal - dVal + 34) % 7;
    int moVal = (dVal + eVal + 114) / 31;
    int daVal = (dVal + eVal + 114) % 31 + 1;
    daVal += 13;
    if (daVal > 30 && moVal == 4)
    {
        daVal -= 30;
        moVal = 5;
    }
    if (daVal > 31 && moVal == 5)
    {
        daVal -= 31;
        moVal = 6;
    }
    return DateTime(daVal, moVal, y);
}