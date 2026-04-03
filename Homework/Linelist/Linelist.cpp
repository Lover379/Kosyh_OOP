#include <iostream>
#include <vector>
#include <locale.h>

using namespace std;

class CircleArr
{
private:
    vector<int> items;

public:
    CircleArr(size_t cnt)
    {
        items.resize(cnt);
        for (size_t i = 0; i < cnt; ++i)
            items[i] = i + 1;
    }

    size_t length() const
    {
        return items.size();
    }

    void eraseAt(size_t pos)
    {
        items.erase(items.begin() + pos);
    }

    int at(size_t pos) const
    {
        return items[pos];
    }
};

size_t solveJosephus(size_t total, size_t step)
{
    CircleArr circle(total);
    size_t idx = 0;

    while (circle.length() > 1)
    {
        idx = (idx + step - 1) % circle.length();
        circle.eraseAt(idx);
    }

    return circle.at(0);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    const size_t step = 3;
    vector<size_t> totals = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };

    cout << "N---------------Answer" << endl;

    for (size_t total : totals)
    {
        size_t ans = solveJosephus(total, step);
        cout << total << "------------" << ans << endl;
    }

    return 0;
}