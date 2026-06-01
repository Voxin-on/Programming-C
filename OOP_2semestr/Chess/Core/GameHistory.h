#ifndef GAME_HISTORY_H
#define GAME_HISTORY_H

#include "Core/ChessTypes.h"

#include <string>

// Запись одного хода в истории
struct HistoryEntry {
    int moveNumber;
    Color player;
    Move move;
};

// История ходов и ключи позиций (ничья по повтору)
class GameHistory {
public:
    GameHistory();
    ~GameHistory();

    GameHistory(const GameHistory& other);
    GameHistory& operator=(const GameHistory& other);

    void addMove(const Move& move, int fullMoveNumber);
    void recordPosition(const std::string& positionKey);
    int countPosition(const std::string& positionKey) const;

    int size() const;
    const HistoryEntry& getEntry(int index) const;

    std::string formatAll() const;

private:
    HistoryEntry* entries_;
    int entrySize_;
    int entryCapacity_;

    std::string* positionKeys_;
    int positionSize_;
    int positionCapacity_;

    void reserveEntries(int newCapacity);
    void reservePositions(int newCapacity);
    void clearAll();
};

#endif
