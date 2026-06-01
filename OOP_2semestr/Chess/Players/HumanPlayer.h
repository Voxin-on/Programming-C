#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Players/Player.h"

class IPlayerInput;

// Интерактивный человек: ввод через IPlayerInput.
class HumanPlayer : public Player {
public:
    HumanPlayer(Color color, IPlayerInput* input);

    HumanPlayer(const HumanPlayer& other);
    HumanPlayer& operator=(const HumanPlayer& other);
    ~HumanPlayer() override;

    bool requestMove(Board& board, Move& outMove) override;
    const char* getName() const override;
    // true — повтор ввода после неправильного хода.
    bool allowsRetryOnIllegalMove() const override;

private:
    IPlayerInput* input_;
    // Проверка: пешка достигает последней горизонтали.
    bool isPawnPromotionMove(Board& board, const Move& move) const;
};

#endif
