#include "AI/MinimaxAlphaBetaStrategy.h"

#include "Pieces/Piece.h"

#include <climits>
#include <vector>

// Конструктор: задаёт глубину поиска.
MinimaxAlphaBetaStrategy::MinimaxAlphaBetaStrategy(int searchDepth)
    : searchDepth_(searchDepth) {}

// Копирование глубины поиска.
MinimaxAlphaBetaStrategy::MinimaxAlphaBetaStrategy(const MinimaxAlphaBetaStrategy& other)
    : searchDepth_(other.searchDepth_) {}

// Присваивание глубины поиска.
MinimaxAlphaBetaStrategy& MinimaxAlphaBetaStrategy::operator=(
    const MinimaxAlphaBetaStrategy& other) {
    if (this != &other) {
        searchDepth_ = other.searchDepth_;
    }
    return *this;
}

// Копия стратегии для AIPlayer
AIStrategy* MinimaxAlphaBetaStrategy::clone() const {
    return new MinimaxAlphaBetaStrategy(*this);
}

// Материальная оценка позиции с точки зрения aiColor.
int MinimaxAlphaBetaStrategy::evaluateBoard(const Board& board, Color aiColor) const {
    int score = 0;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            const Piece* piece = board.getPiece(r, c);
            if (piece == nullptr) {
                continue;
            }
            const int value = pieceMaterialValue(piece->getType());
            if (piece->getColor() == aiColor) {
                score += value;
            } else {
                score -= value;
            }
        }
    }
    return score;
}

// Рекурсивный минимакс с альфа-бета отсечением.
int MinimaxAlphaBetaStrategy::minimax(Board& board, int depth, int alpha, int beta,
                                      bool maximizing, Color aiColor) const {
    const Color side = maximizing ? aiColor : oppositeColor(aiColor);
    const std::vector<Move> moves = board.generateLegalMoves(side);

    if (moves.empty()) {
        // Мат или пат: большой штраф/бонус в зависимости от стороны.
        if (board.isKingInCheck(side)) {
            return maximizing ? -100000 : 100000;
        }
        return 0;
    }
    if (depth == 0) {
        return evaluateBoard(board, aiColor);
    }

    if (maximizing) {
        int maxEval = INT_MIN;
        for (const Move& move : moves) {
            const MoveUndo undo = board.makeMove(move);
            const int eval = minimax(board, depth - 1, alpha, beta, false, aiColor);
            board.unmakeMove(undo);
            if (eval > maxEval) {
                maxEval = eval;
            }
            if (eval > alpha) {
                alpha = eval;
            }
            // Альфа-бета отсечение.
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    }

    int minEval = INT_MAX;
    for (const Move& move : moves) {
        const MoveUndo undo = board.makeMove(move);
        const int eval = minimax(board, depth - 1, alpha, beta, true, aiColor);
        board.unmakeMove(undo);
        if (eval < minEval) {
            minEval = eval;
        }
        if (eval < beta) {
            beta = eval;
        }
        // Альфа-бета отсечение.
        if (beta <= alpha) {
            break;
        }
    }
    return minEval;
}

// Выбор хода с максимальной оценкой на копии доски.
bool MinimaxAlphaBetaStrategy::chooseMove(Board& board, Color aiColor, Move& outMove) {
    const std::vector<Move> moves = board.generateLegalMoves(aiColor);
    if (moves.empty()) {
        return false;
    }

    // Поиск на копии — реальная доска партии не меняется до playTurn().
    Board searchBoard(board);

    int bestScore = INT_MIN;
    Move bestMove = moves[0];
    bool found = false;

    // Минимальная глубина — один полуход.
    const int depth = searchDepth_ > 0 ? searchDepth_ : 1;

    for (const Move& move : moves) {
        const MoveUndo undo = searchBoard.makeMove(move);
        const int score =
            minimax(searchBoard, depth - 1, INT_MIN, INT_MAX, false, aiColor);
        searchBoard.unmakeMove(undo);

        if (!found || score > bestScore) {
            bestScore = score;
            bestMove = move;
            found = true;
        }
    }

    outMove = bestMove;
    return found;
}
