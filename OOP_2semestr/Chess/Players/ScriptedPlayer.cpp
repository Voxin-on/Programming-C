#include "Players/ScriptedPlayer.h"

#include "Core/Board.h"
#include "Pieces/Piece.h"

// Конструктор: копирование сценарного списка ходов.
ScriptedPlayer::ScriptedPlayer(Color color, const Move* scriptedMoves, int scriptedCount)
    : Player(color), scriptedMoves_(nullptr), scriptedCount_(0), nextIndex_(0) {
    copyScriptedMoves(scriptedMoves, scriptedCount);
}

// Освобождение буфера сценарных ходов.
ScriptedPlayer::~ScriptedPlayer() { releaseScriptedMoves(); }

// Глубокое копирование сценария и индекса следующего хода.
ScriptedPlayer::ScriptedPlayer(const ScriptedPlayer& other)
    : Player(other), scriptedMoves_(nullptr), scriptedCount_(0), nextIndex_(other.nextIndex_) {
    copyScriptedMoves(other.scriptedMoves_, other.scriptedCount_);
}

// Присваивание с пересозданием буфера ходов.
ScriptedPlayer& ScriptedPlayer::operator=(const ScriptedPlayer& other) {
    if (this != &other) {
        Player::operator=(other);
        releaseScriptedMoves();
        nextIndex_ = other.nextIndex_;
        copyScriptedMoves(other.scriptedMoves_, other.scriptedCount_);
    }
    return *this;
}

// Копирование массива сценарных ходов с подстановкой цвета.
void ScriptedPlayer::copyScriptedMoves(const Move* moves, int count) {
    releaseScriptedMoves();
    if (count <= 0 || moves == nullptr) {
        return;
    }
    scriptedCount_ = count;
    scriptedMoves_ = new Move[count];
    for (int i = 0; i < count; ++i) {
        scriptedMoves_[i] = moves[i];
        scriptedMoves_[i].player = color_;
    }
}

// Освобождение буфера сценарных ходов.
void ScriptedPlayer::releaseScriptedMoves() {
    delete[] scriptedMoves_;
    scriptedMoves_ = nullptr;
    scriptedCount_ = 0;
}

// Возвращает следующий легальный ход из сценария (нелегальные пропускаются).
bool ScriptedPlayer::requestMove(Board& board, Move& outMove) {
    while (nextIndex_ < scriptedCount_) {
        Move candidate = scriptedMoves_[nextIndex_];
        ++nextIndex_;
        candidate.player = color_;
        const Piece* piece = board.getPiece(candidate.from.row, candidate.from.col);
        if (piece != nullptr && piece->getType() == PieceType::Pawn) {
            const bool promotionRank =
                (color_ == Color::White && candidate.to.row == 0) ||
                (color_ == Color::Black && candidate.to.row == 7);
            if (promotionRank) {
                candidate.isPromotion = true;
                // Неверный тип превращения — по умолчанию ферзь.
                if (!isPromotionPiece(candidate.promotionTo)) {
                    candidate.promotionTo = PieceType::Queen;
                }
            }
        }
        if (board.isLegalMove(candidate)) {
            if (piece != nullptr) {
                candidate.pieceType = piece->getType();
            }
            const Piece* cap = board.getPiece(candidate.to.row, candidate.to.col);
            candidate.isCapture = cap != nullptr && cap->getColor() != color_;
            candidate.capturedType =
                candidate.isCapture ? cap->getType() : PieceType::None;
            outMove = candidate;
            return true;
        }
    }
    return false;
}

// Имя игрока для вывода в интерфейсе.
const char* ScriptedPlayer::getName() const { return "Scripted"; }
