#include "Core/ChessTypes.h"

// Позиция по умолчанию
Position::Position() : row(0), col(0) {}

// Позиция с координатами
Position::Position(int r, int c) : row(r), col(c) {}

// Клетка внутри доски 8x8
bool Position::isOnBoard() const {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

// Сравнение координат
bool Position::operator==(const Position& other) const {
    return row == other.row && col == other.col;
}

// Пустой ход
Move::Move()
    : from(),
      to(),
      player(Color::White),
      pieceType(PieceType::None),
      capturedType(PieceType::None),
      isCapture(false),
      isPromotion(false),
      promotionTo(PieceType::Queen) {}

// Противоположный цвет
Color oppositeColor(Color color) {
    return color == Color::White ? Color::Black : Color::White;
}

// Имя цвета для вывода
std::string colorToString(Color color) {
    return color == Color::White ? "White" : "Black";
}

// Имя типа фигуры
std::string pieceTypeToString(PieceType type) {
    switch (type) {
        case PieceType::Pawn: return "Pawn";
        case PieceType::Knight: return "Knight";
        case PieceType::Bishop: return "Bishop";
        case PieceType::Rook: return "Rook";
        case PieceType::Queen: return "Queen";
        case PieceType::King: return "King";
        default: return "None";
    }
}

// Материальная оценка для minimax
int pieceMaterialValue(PieceType type) {
    switch (type) {
        case PieceType::Pawn: return 10;
        case PieceType::Knight: return 30;
        case PieceType::Bishop: return 30;
        case PieceType::Rook: return 50;
        case PieceType::Queen: return 90;
        case PieceType::King: return 900;
        default: return 0;
    }
}

// Допустимая фигура при превращении
bool isPromotionPiece(PieceType type) {
    return type == PieceType::Queen || type == PieceType::Rook ||
           type == PieceType::Bishop || type == PieceType::Knight;
}

// Буква фигуры для ввода превращения
char promotionPieceToChar(PieceType type) {
    switch (type) {
        case PieceType::Queen: return 'Q';
        case PieceType::Rook: return 'R';
        case PieceType::Bishop: return 'B';
        case PieceType::Knight: return 'N';
        default: return '?';
    }
}
