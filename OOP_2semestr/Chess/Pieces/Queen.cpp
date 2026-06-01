#include "Pieces/Queen.h"

#include "Core/Board.h"

#include <cmath>

// конструктор ферзя
Queen::Queen(Color color, int row, int col) : Piece(color, row, col) {}

// клонирование ферзя
Piece* Queen::clone() const { return new Queen(*this); }
// тип фигуры
PieceType Queen::getType() const { return PieceType::Queen; }
// символ для отображения
char Queen::getSymbol() const { return color_ == Color::White ? 'Q' : 'q'; }

// проверка хода ферзём
bool Queen::isValidMove(const Board& board, int toRow, int toCol) const {
    const bool straight = (row_ == toRow || col_ == toCol);
    const bool diagonal = std::abs(toRow - row_) == std::abs(toCol - col_);
    if (!straight && !diagonal) { // не по линии и не по диагонали
        return false;
    }
    const Piece* target = board.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color_) { // нельзя бить свою фигуру
        return false;
    }
    return board.isPathClear(row_, col_, toRow, toCol);
}
