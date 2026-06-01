#ifndef PIECE_H
#define PIECE_H

#include "Core/ChessTypes.h"

class Board;

class Piece {
public:
    // конструктор фигуры
    Piece(Color color, int row, int col);
    // деструктор фигуры
    virtual ~Piece();

    // копирование фигуры
    Piece(const Piece& other);
    // присваивание фигуры
    Piece& operator=(const Piece& other);

    // клонирование фигуры
    virtual Piece* clone() const = 0;
    // тип фигуры
    virtual PieceType getType() const = 0;
    // символ для отображения
    virtual char getSymbol() const = 0;
    // проверка допустимости хода
    virtual bool isValidMove(const Board& board, int toRow, int toCol) const = 0;

    // получение цвета
    Color getColor() const;
    // получение строки
    int getRow() const;
    // получение столбца
    int getCol() const;
    // проверка, двигалась ли фигура
    bool hasMoved() const;
    // установка позиции
    void setPosition(int row, int col);
    // установка флага хода
    void setHasMoved(bool moved);

protected:
    Color color_;
    int row_;
    int col_;
    bool hasMoved_;
};

#endif
