#include "Pieces/Knight.h"

#include "Core/Board.h"

#include <cmath>

// конструктор коня
Knight::Knight(Color color, int row, int col) : Piece(color, row, col) {}

// клонирование коня
Piece* Knight::clone() const { return new Knight(*this); }
// тип фигуры
PieceType Knight::getType() const { return PieceType::Knight; }
// символ для отображения
char Knight::getSymbol() const { return color_ == Color::White ? 'N' : 'n'; }

// проверка хода конём
bool Knight::isValidMove(const Board& board, int toRow, int toCol) const {
    const int dr = std::abs(toRow - row_);
    const int dc = std::abs(toCol - col_);
    if (!((dr == 2 && dc == 1) || (dr == 1 && dc == 2))) { // не L-образный ход
        return false;
    }
    const Piece* target = board.getPiece(toRow, toCol);
    return target == nullptr || target->getColor() != color_;
}
