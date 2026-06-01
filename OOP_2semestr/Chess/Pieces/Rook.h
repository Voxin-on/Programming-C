#ifndef ROOK_H
#define ROOK_H

#include "Pieces/Piece.h"

class Rook : public Piece {
public:
    // конструктор ладьи
    Rook(Color color, int row, int col);
    // клонирование ладьи
    Piece* clone() const override;
    // тип фигуры
    PieceType getType() const override;
    // символ для отображения
    char getSymbol() const override;
    // проверка хода ладьёй
    bool isValidMove(const Board& board, int toRow, int toCol) const override;
};

#endif
