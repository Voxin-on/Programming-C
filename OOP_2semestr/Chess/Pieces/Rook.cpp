#include "Pieces/Rook.h"

#include "Core/Board.h"

// конструктор ладьи
Rook::Rook(Color color, int row, int col) : Piece(color, row, col) {}

// клонирование ладьи
Piece* Rook::clone() const { return new Rook(*this); }
// тип фигуры
PieceType Rook::getType() const { return PieceType::Rook; }
// символ для отображения
char Rook::getSymbol() const { return color_ == Color::White ? 'R' : 'r'; }

// проверка хода ладьёй
bool Rook::isValidMove(const Board& board, int toRow, int toCol) const {
    if (row_ != toRow && col_ != toCol) { // не по горизонтали и не по вертикали
        return false;
    }
    const Piece* target = board.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color_) { // нельзя бить свою фигуру
        return false;
    }
    return board.isPathClear(row_, col_, toRow, toCol);
}
