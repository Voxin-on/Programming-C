#ifndef SCRIPTED_PLAYER_H
#define SCRIPTED_PLAYER_H

#include "Players/Player.h"

// Заранее заданные ходы (для автотестов).
class ScriptedPlayer : public Player {
public:
    ScriptedPlayer(Color color, const Move* scriptedMoves, int scriptedCount);

    ScriptedPlayer(const ScriptedPlayer& other);
    ScriptedPlayer& operator=(const ScriptedPlayer& other);
    ~ScriptedPlayer() override;

    // Следующий легальный ход из сценария (нелегальные пропускаются).
    bool requestMove(Board& board, Move& outMove) override;
    const char* getName() const override;

private:
    Move* scriptedMoves_;
    int scriptedCount_;
    int nextIndex_;

    // Копирование массива сценарных ходов с подстановкой цвета.
    void copyScriptedMoves(const Move* moves, int count);
    // Освобождение буфера сценарных ходов.
    void releaseScriptedMoves();
};

#endif
