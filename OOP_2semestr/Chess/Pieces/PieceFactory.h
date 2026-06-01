#ifndef PIECE_FACTORY_H
#define PIECE_FACTORY_H

#include "Core/ChessTypes.h"

class Piece;

// создание фигуры по типу
Piece* createPiece(PieceType type, Color color, int row, int col);

#endif
