#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Players/Player.h"

class AIStrategy;

// Компьютер: делегирует выбор хода стратегии ИИ.
class AIPlayer : public Player {
public:
    AIPlayer(Color color, AIStrategy* strategy);
    ~AIPlayer() override;

    AIPlayer(const AIPlayer& other);
    AIPlayer& operator=(const AIPlayer& other);

    // Делегирование выбора хода стратегии ИИ.
    bool requestMove(Board& board, Move& outMove) override;
    const char* getName() const override;

    // Замена стратегии (старая удаляется).
    void setStrategy(AIStrategy* strategy);

private:
    AIStrategy* strategy_;

    // Удаление текущей стратегии.
    void releaseStrategy();
    // Глубокая копия стратегии (или nullptr).
    AIStrategy* cloneStrategy(const AIStrategy* source) const;
};

#endif
