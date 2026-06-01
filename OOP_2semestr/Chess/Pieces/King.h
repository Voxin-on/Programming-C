#ifndef KING_H
#define KING_H

#include "Pieces/Piece.h"

class King : public Piece {
public:
    // конструктор короля
    King(Color color, int row, int col);
    // клонирование короля
    Piece* clone() const override;
    // тип фигуры
    PieceType getType() const override;
    // символ для отображения
    char getSymbol() const override;
    // проверка хода королём
    bool isValidMove(const Board& board, int toRow, int toCol) const override;
};

#endif
