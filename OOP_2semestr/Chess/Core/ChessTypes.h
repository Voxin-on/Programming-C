#ifndef CHESS_TYPES_H
#define CHESS_TYPES_H

#include <string>

// Цвет стороны
enum class Color {
    White,
    Black
};

// Тип фигуры
enum class PieceType {
    None,
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

// Клетка доски (row 0 = 8-я горизонталь)
struct Position {
    int row;
    int col;

    Position();
    Position(int r, int c);
    bool isOnBoard() const;
    bool operator==(const Position& other) const;
};

// Описание хода
struct Move {
    Position from;
    Position to;
    Color player;
    PieceType pieceType;
    PieceType capturedType;
    bool isCapture;
    bool isPromotion;
    PieceType promotionTo;

    Move();
};

// Снимок для отмены хода
struct MoveUndo {
    Move move;
    bool capturedHadMoved;
    bool movedPieceHadMoved;
    bool rookHadMovedBefore;
    bool enPassantCapture;
    Position enPassantTargetBefore;
    bool enPassantValidBefore;
    int halfMoveClockBefore;
    int fullMoveNumberBefore;
};

Color oppositeColor(Color color);
std::string colorToString(Color color);
std::string pieceTypeToString(PieceType type);
int pieceMaterialValue(PieceType type);
bool isPromotionPiece(PieceType type);
char promotionPieceToChar(PieceType type);

#endif
