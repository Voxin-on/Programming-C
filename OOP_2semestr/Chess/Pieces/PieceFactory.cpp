#include "Pieces/PieceFactory.h"

#include "Pieces/Bishop.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"

// создание фигуры по типу
Piece* createPiece(PieceType type, Color color, int row, int col) {
    switch (type) {
        case PieceType::Pawn:
            return new Pawn(color, row, col);
        case PieceType::Rook:
            return new Rook(color, row, col);
        case PieceType::Knight:
            return new Knight(color, row, col);
        case PieceType::Bishop:
            return new Bishop(color, row, col);
        case PieceType::Queen:
            return new Queen(color, row, col);
        case PieceType::King:
            return new King(color, row, col);
        default:
            return nullptr; // неизвестный тип
    }
}
