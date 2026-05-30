#include "four_v_ryad.h"
#include <iostream>

using namespace std;

Field::Field(bool startWithRed) {
    redTurn = startWithRed;
    winner = EMPTY;
    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            cells[i][j] = EMPTY;
        }
    }
}

bool Field::isRedTurnNow() const {
    return redTurn;
}

bool Field::checkLine(int startX, int startY, int dx, int dy) const {
    CellState first = cells[startX][startY];
    if (first == EMPTY) return false;

    for (int i = 1; i < 4; i++) {
        int x = startX + i * dx;
        int y = startY + i * dy;
        if (cells[x][y] != first) return false;
    }
    return true;
}

bool Field::isOver() {
    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            if (i <= FIELD_WIDTH - 4 && checkLine(i, j, 1, 0)) { winner = cells[i][j]; return true; }
            if (j <= FIELD_HEIGHT - 4 && checkLine(i, j, 0, 1)) { winner = cells[i][j]; return true; }
            if (i <= FIELD_WIDTH - 4 && j <= FIELD_HEIGHT - 4 && checkLine(i, j, 1, 1)) { winner = cells[i][j]; return true; }
            if (i <= FIELD_WIDTH - 4 && j >= 3 && checkLine(i, j, 1, -1)) { winner = cells[i][j]; return true; }
        }
    }

    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            if (cells[i][j] == EMPTY) return false;
        }
    }

    winner = EMPTY;
    return true;
}

bool Field::makeTurn(int column) {
    int colIdx = column - 1;
    if (colIdx < 0 || colIdx >= FIELD_WIDTH) return false;

    for (int j = 0; j < FIELD_HEIGHT; j++) {
        if (cells[colIdx][j] == EMPTY) {
            cells[colIdx][j] = redTurn ? RED : YELLOW;
            redTurn = !redTurn;
            return true;
        }
    }
    return false;
}

void Field::print() const {
    cout << "\n 1 2 3 4 5 6 7\n";
    cout << "-----------------\n";
    for (int j = FIELD_HEIGHT - 1; j >= 0; j--) {
        cout << "|";
        for (int i = 0; i < FIELD_WIDTH; i++) {
            if (cells[i][j] == RED) cout << "R ";
            else if (cells[i][j] == YELLOW) cout << "Y ";
            else cout << ". ";
        }
        cout << "|\n";
    }
    cout << "-----------------\n";
}

void Field::printResult() const {
    if (winner == RED) cout << "Победил красный игрок!" << endl;
    else if (winner == YELLOW) cout << "Победил желтый игрок!" << endl;
    else cout << "Ничья! Все клетки заполнены." << endl;
}