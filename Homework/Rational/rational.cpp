#include "rational.h"
#include <cmath>
#include <iostream>
#include <locale.h>

using namespace std;

void Rational::reduce()
{
    if (dn < 0)
    {
        nm = -nm;
        dn = -dn;
    }

    int x = std::abs(nm);
    int y = std::abs(dn);

    while (y != 0)
    {
        int temp = y;
        y = x % y;
        x = temp;
    }

    if (x > 1)
    {
        nm /= x;
        dn /= x;
    }
}

Rational::Rational() : nm(0), dn(1) {}

Rational::Rational(int n) : nm(n), dn(1) {}

Rational::Rational(int n, int d) : nm(n), dn(d)
{
    reduce();
}

Rational Rational::operator-() const
{
    return Rational(-nm, dn);
}

Rational& Rational::operator+=(const Rational& r)
{
    nm = nm * r.dn + r.nm * dn;
    dn = dn * r.dn;
    reduce();
    return *this;
}

Rational& Rational::operator-=(const Rational& r)
{
    return *this += -r;
}

Rational Rational::operator+(const Rational& r) const
{
    Rational tmp(*this);
    return tmp += r;
}

Rational Rational::operator-(const Rational& r) const
{
    Rational tmp(*this);
    return tmp -= r;
}

Rational& Rational::operator++()
{
    nm += dn;
    return *this;
}

Rational Rational::operator++(int)
{
    Rational tmp(*this);
    nm += dn;
    return tmp;
}

bool Rational::operator==(const Rational& r) const
{
    return nm == r.nm && dn == r.dn;
}

bool Rational::operator!=(const Rational& r) const
{
    return !(*this == r);
}

Rational::operator int() const
{
    return nm / dn;
}

Rational::operator double() const
{
    return (double)nm / dn;
}

std::istream& operator>>(std::istream& in, Rational& r)
{
    in >> r.nm >> r.dn;
    r.reduce();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Rational& r)
{
    out << r.nm << "/" << r.dn;
    return out;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Rational x(1, 2), y(-1, 6);
    cout << "x = " << x << ", y = " << y << endl;

    cout << "x + y = " << x + y << endl;
    cout << "x - y = " << x - y << endl;

    Rational z = x;
    z += y;
    cout << "x += y => " << z << endl;

    cout << "++x = " << ++x << endl;
    cout << "x++ = " << x++ << ", after: x = " << x << endl;

    cout << "x == y: " << (x == y ? "true" : "false") << endl;
    cout << "x != y: " << (x != y ? "true" : "false") << endl;

    cout << "x as double = " << (double)x << endl;
    cout << "x as int    = " << (int)x << endl;

    Rational w;
    cout << "Enter fraction (numerator denominator): ";
    cin >> w;
    cout << "You entered: " << w << endl;

    return 0;
}