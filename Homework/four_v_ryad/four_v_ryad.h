#ifndef FOUR_V_RYAD_H
#define FOUR_V_RYAD_H

const int FIELD_WIDTH = 7;
const int FIELD_HEIGHT = 6;

enum CellState {
    EMPTY = 0,
    RED = 1,
    YELLOW = 2
};

class Field {
private:
    CellState cells[FIELD_WIDTH][FIELD_HEIGHT];
    bool redTurn;
    CellState winner;

    bool checkLine(int startX, int startY, int dx, int dy) const;

public:
    Field(bool startWithRed = true);

    bool isRedTurnNow() const;
    bool isOver();
    bool makeTurn(int column);
    void print() const;
    void printResult() const;
};

#endif