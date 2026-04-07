#pragma once
#include <iostream>

using namespace std;

class DateTime
{
private:
    int dy;
    int mn;
    int yr;
    int hr;
    int min;
    int sec;

    bool leapYear(int y) const;
    int monthDays(int m, int y) const;
    long long totalDays() const;

public:
    DateTime();
    DateTime(int d, int m, int y, int hh = 0, int mm = 0, int ss = 0);

    bool checkDate(int d, int m, int y) const;
    void inputDate();
    void validateAndFix();

    void showFormat1() const;
    void showFormat2() const;
    void showFormat3() const;
    void showISO() const;

    long long daysBetween(const DateTime& other) const;
    const char* weekDay() const;

    bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator>(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;

    DateTime operator+(int days) const;
    DateTime operator-(int days) const;
    int operator-(const DateTime& other) const;

    friend ostream& operator<<(ostream& os, const DateTime& dt);
    friend istream& operator>>(istream& is, DateTime& dt);

    static DateTime catholikEaster(int y);
    static DateTime orthodoxEaster(int y);
};
