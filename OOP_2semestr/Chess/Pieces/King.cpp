#include "Pieces/King.h"

#include "Core/Board.h"

#include <cmath>

// конструктор короля
King::King(Color color, int row, int col) : Piece(color, row, col) {}

// клонирование короля
Piece* King::clone() const { return new King(*this); }
// тип фигуры
PieceType King::getType() const { return PieceType::King; }
// символ для отображения
char King::getSymbol() const { return color_ == Color::White ? 'K' : 'k'; }

// проверка хода королём
bool King::isValidMove(const Board& board, int toRow, int toCol) const {
    const int dr = std::abs(toRow - row_);
    const int dc = std::abs(toCol - col_);
    if (dr <= 1 && dc <= 1 && (dr + dc > 0)) { // обычный ход на одну клетку
        const Piece* target = board.getPiece(toRow, toCol);
        return target == nullptr || target->getColor() != color_;
    }

    if (!hasMoved_ && row_ == toRow && dr == 0 && dc == 2) { // рокировка
        const int rookCol = (toCol > col_) ? 7 : 0;
        const Piece* rook = board.getPiece(row_, rookCol);
        if (rook != nullptr && rook->getType() == PieceType::Rook && !rook->hasMoved() &&
            board.isPathClear(row_, col_, row_, toCol) &&
            board.isCastlingPathSafe(row_, col_, toCol, color_)) { // условия рокировки
            return true;
        }
    }
    return false;
}
