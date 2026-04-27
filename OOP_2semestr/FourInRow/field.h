#ifndef FIELD_H
#define FIELD_H

enum Cell{
    EMPTY,
    RED,
    YELLOW
};

const int FIELD_WIDTH = 7;
const int FIELD_HEIGHT = 6;

class Field{
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT];
    // Очередь хода
    bool isRedTurn;
    // Кто на данный момент выиграл
    Cell winner;
    void checkWinner();
public:
    Field(bool isRedFirst);
    void clear(bool isRedFirst);
    bool makeTurn(int column);
    bool isWon(bool red) const;
    bool isOver() const;
    Cell getCell(int i, int j) const;
    bool isRedTurnNow() const;
    void print() const;
    void printResult() const;
};

#endif