#include "Pieces/Piece.h"

// конструктор фигуры
Piece::Piece(Color color, int row, int col)
    : color_(color), row_(row), col_(col), hasMoved_(false) {}

// деструктор фигуры
Piece::~Piece() = default;

// копирование фигуры
Piece::Piece(const Piece& other)
    : color_(other.color_),
      row_(other.row_),
      col_(other.col_),
      hasMoved_(other.hasMoved_) {}

// присваивание фигуры
Piece& Piece::operator=(const Piece& other) {
    if (this != &other) { // защита от самоприсваивания
        color_ = other.color_;
        row_ = other.row_;
        col_ = other.col_;
        hasMoved_ = other.hasMoved_;
    }
    return *this;
}

// получение цвета
Color Piece::getColor() const { return color_; }
// получение строки
int Piece::getRow() const { return row_; }
// получение столбца
int Piece::getCol() const { return col_; }
// проверка, двигалась ли фигура
bool Piece::hasMoved() const { return hasMoved_; }

// установка позиции
void Piece::setPosition(int row, int col) {
    row_ = row;
    col_ = col;
}

// установка флага хода
void Piece::setHasMoved(bool moved) { hasMoved_ = moved; }
