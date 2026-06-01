#ifndef QUEEN_H
#define QUEEN_H

#include "Pieces/Piece.h"

class Queen : public Piece {
public:
    // конструктор ферзя
    Queen(Color color, int row, int col);
    // клонирование ферзя
    Piece* clone() const override;
    // тип фигуры
    PieceType getType() const override;
    // символ для отображения
    char getSymbol() const override;
    // проверка хода ферзём
    bool isValidMove(const Board& board, int toRow, int toCol) const override;
};

#endif
