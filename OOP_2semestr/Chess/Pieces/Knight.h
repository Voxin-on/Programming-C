#ifndef KNIGHT_H
#define KNIGHT_H

#include "Pieces/Piece.h"

class Knight : public Piece {
public:
    // конструктор коня
    Knight(Color color, int row, int col);
    // клонирование коня
    Piece* clone() const override;
    // тип фигуры
    PieceType getType() const override;
    // символ для отображения
    char getSymbol() const override;
    // проверка хода конём
    bool isValidMove(const Board& board, int toRow, int toCol) const override;
};

#endif
