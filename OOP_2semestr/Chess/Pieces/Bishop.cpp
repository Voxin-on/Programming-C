#include "Pieces/Bishop.h"

#include "Core/Board.h"

#include <cmath>

// конструктор слона
Bishop::Bishop(Color color, int row, int col) : Piece(color, row, col) {}

// клонирование слона
Piece* Bishop::clone() const { return new Bishop(*this); }
// тип фигуры
PieceType Bishop::getType() const { return PieceType::Bishop; }
// символ для отображения
char Bishop::getSymbol() const { return color_ == Color::White ? 'B' : 'b'; }

// проверка хода слоном
bool Bishop::isValidMove(const Board& board, int toRow, int toCol) const {
    if (std::abs(toRow - row_) != std::abs(toCol - col_)) { // не по диагонали
        return false;
    }
    const Piece* target = board.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color_) { // нельзя бить свою фигуру
        return false;
    }
    return board.isPathClear(row_, col_, toRow, toCol);
}
