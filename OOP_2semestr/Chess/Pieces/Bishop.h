#ifndef BISHOP_H
#define BISHOP_H

#include "Pieces/Piece.h"

class Bishop : public Piece {
public:
    // конструктор слона
    Bishop(Color color, int row, int col);
    // клонирование слона
    Piece* clone() const override;
    // тип фигуры
    PieceType getType() const override;
    // символ для отображения
    char getSymbol() const override;
    // проверка хода слоном
    bool isValidMove(const Board& board, int toRow, int toCol) const override;
};

#endif
