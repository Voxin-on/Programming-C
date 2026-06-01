#ifndef PAWN_H
#define PAWN_H

#include "Pieces/Piece.h"

class Pawn : public Piece {
public:
    // конструктор пешки
    Pawn(Color color, int row, int col);
    // клонирование пешки
    Piece* clone() const override;
    // тип фигуры
    PieceType getType() const override;
    // символ для отображения
    char getSymbol() const override;
    // проверка хода пешкой
    bool isValidMove(const Board& board, int toRow, int toCol) const override;
};

#endif
