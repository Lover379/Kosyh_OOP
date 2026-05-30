#include <iostream>
#include "four_v_ryad.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "Russian");
    Field field(true);

    while (!field.isOver()) {
        field.print();
        cout << "Ходит " << (field.isRedTurnNow() ? "красный" : "желтый")
            << " игрок, введите ход (1-7)" << endl;
        int column;
        cin >> column;

        while (!field.makeTurn(column)) {
            cout << "Неверный ход или колонка полна! Введите заново (1-7):" << endl;
            cin >> column;
        }
    }

    field.print();
    field.printResult();
    return 0;
}