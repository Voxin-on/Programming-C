#include "Players/AIPlayer.h"

#include "AI/AIStrategy.h"
#include "Core/Board.h"

// Конструктор: владение указателем на стратегию ИИ.
AIPlayer::AIPlayer(Color color, AIStrategy* strategy) : Player(color), strategy_(strategy) {}

// Удаление стратегии при уничтожении игрока.
AIPlayer::~AIPlayer() { releaseStrategy(); }

// Глубокая копия стратегии.
AIPlayer::AIPlayer(const AIPlayer& other)
    : Player(other), strategy_(cloneStrategy(other.strategy_)) {}

// Глубокое присваивание стратегии.
AIPlayer& AIPlayer::operator=(const AIPlayer& other) {
    if (this != &other) {
        Player::operator=(other);
        releaseStrategy();
        strategy_ = cloneStrategy(other.strategy_);
    }
    return *this;
}

// Копия полиморфной стратегии.
AIStrategy* AIPlayer::cloneStrategy(const AIStrategy* source) const {
    if (source == nullptr) {
        return nullptr;
    }
    return source->clone();
}

// Удаление текущей стратегии.
void AIPlayer::releaseStrategy() {
    delete strategy_;
    strategy_ = nullptr;
}

// Замена стратегии (старая удаляется).
void AIPlayer::setStrategy(AIStrategy* strategy) {
    releaseStrategy();
    strategy_ = strategy;
}

// Делегирование выбора хода стратегии ИИ.
bool AIPlayer::requestMove(Board& board, Move& outMove) {
    if (strategy_ == nullptr) {
        return false;
    }
    return strategy_->chooseMove(board, color_, outMove);
}

// Имя игрока для вывода в интерфейсе.
const char* AIPlayer::getName() const { return "AI (Minimax)"; }
