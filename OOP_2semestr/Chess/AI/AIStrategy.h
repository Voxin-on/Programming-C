#ifndef AI_STRATEGY_H
#define AI_STRATEGY_H

#include "Core/Board.h"
#include "Core/ChessTypes.h"

// Интерфейс стратегии ИИ (Strategy)
class AIStrategy {
public:
    virtual ~AIStrategy();

    // Выбрать ход для стороны aiColor
    virtual bool chooseMove(Board& board, Color aiColor, Move& outMove) = 0;
    // Копия стратегии для глубокого копирования AIPlayer
    virtual AIStrategy* clone() const = 0;
};

#endif
