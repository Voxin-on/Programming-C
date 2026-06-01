#include "Pieces/Pawn.h"

#include "Core/Board.h"

#include <cmath>

// конструктор пешки
Pawn::Pawn(Color color, int row, int col) : Piece(color, row, col) {}

// клонирование пешки
Piece* Pawn::clone() const { return new Pawn(*this); }
// тип фигуры
PieceType Pawn::getType() const { return PieceType::Pawn; }
// символ для отображения
char Pawn::getSymbol() const { return color_ == Color::White ? 'P' : 'p'; }

// проверка хода пешкой
bool Pawn::isValidMove(const Board& board, int toRow, int toCol) const {
    const int direction = (color_ == Color::White) ? -1 : 1;
    const int startRow = (color_ == Color::White) ? 6 : 1;
    const Piece* target = board.getPiece(toRow, toCol);

    if (toCol == col_) { // ход по вертикали
        if (toRow == row_ + direction && target == nullptr) { // шаг на одну клетку вперёд
            return true;
        }
        if (row_ == startRow && toRow == row_ + 2 * direction &&
            board.getPiece(row_ + direction, col_) == nullptr && target == nullptr) { // двойной ход с начальной линии
            return true;
        }
    }

    if (toRow == row_ + direction && std::abs(toCol - col_) == 1) { // диагональный ход
        if (target != nullptr && target->getColor() != color_) { // взятие по диагонали
            return true;
        }
        const Position ep = board.getEnPassantTarget();
        if (ep.row == toRow && ep.col == toCol) { // взятие на проходе
            return true;
        }
    }
    return false;
}
