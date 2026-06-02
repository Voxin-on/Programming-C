#ifndef MINIMAX_ALPHA_BETA_STRATEGY_H
#define MINIMAX_ALPHA_BETA_STRATEGY_H

#include "AI/AIStrategy.h"

// Минимакс с альфа-бета отсечением.
class MinimaxAlphaBetaStrategy : public AIStrategy {
public:
    explicit MinimaxAlphaBetaStrategy(int searchDepth = 3);
    ~MinimaxAlphaBetaStrategy() override = default;

    MinimaxAlphaBetaStrategy(const MinimaxAlphaBetaStrategy& other);
    MinimaxAlphaBetaStrategy& operator=(const MinimaxAlphaBetaStrategy& other);

    // Выбор хода с максимальной оценкой на копии доски.
    bool chooseMove(Board& board, Color aiColor, Move& outMove) override;
    AIStrategy* clone() const override;

private:
    int searchDepth_;

    // Материальная оценка позиции с точки зрения aiColor.
    int evaluateBoard(const Board& board, Color aiColor) const;
    // Рекурсивный минимакс с альфа-бета отсечением.
    int minimax(Board& board, int depth, int alpha, int beta, Color aiColor) const;
};

#endif
