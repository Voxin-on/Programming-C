#include "Core/GameHistory.h"

#include <sstream>

namespace {

// Алгебраическая нотация клетки (a1..h8)
std::string squareName(int row, int col) {
    char file = static_cast<char>('a' + col);
    char rank = static_cast<char>('1' + (7 - row));
    std::string s;
    s.push_back(file);
    s.push_back(rank);
    return s;
}

}  // namespace

// Пустая история
GameHistory::GameHistory()
    : entries_(nullptr),
      entrySize_(0),
      entryCapacity_(0),
      positionKeys_(nullptr),
      positionSize_(0),
      positionCapacity_(0) {}

// Освобождение массивов
GameHistory::~GameHistory() { clearAll(); }

// Копирование истории
GameHistory::GameHistory(const GameHistory& other)
    : entries_(nullptr),
      entrySize_(0),
      entryCapacity_(0),
      positionKeys_(nullptr),
      positionSize_(0),
      positionCapacity_(0) {
    reserveEntries(other.entrySize_);
    for (int i = 0; i < other.entrySize_; ++i) {
        entries_[i] = other.entries_[i];
    }
    entrySize_ = other.entrySize_;

    reservePositions(other.positionSize_);
    for (int i = 0; i < other.positionSize_; ++i) {
        positionKeys_[i] = other.positionKeys_[i];
    }
    positionSize_ = other.positionSize_;
}

// Присваивание с пересозданием буферов
GameHistory& GameHistory::operator=(const GameHistory& other) {
    if (this != &other) {
        clearAll();
        reserveEntries(other.entrySize_);
        for (int i = 0; i < other.entrySize_; ++i) {
            entries_[i] = other.entries_[i];
        }
        entrySize_ = other.entrySize_;

        reservePositions(other.positionSize_);
        for (int i = 0; i < other.positionSize_; ++i) {
            positionKeys_[i] = other.positionKeys_[i];
        }
        positionSize_ = other.positionSize_;
    }
    return *this;
}

// Удаление всех записей
void GameHistory::clearAll() {
    delete[] entries_;
    entries_ = nullptr;
    entrySize_ = 0;
    entryCapacity_ = 0;

    delete[] positionKeys_;
    positionKeys_ = nullptr;
    positionSize_ = 0;
    positionCapacity_ = 0;
}

// Расширение массива ходов
void GameHistory::reserveEntries(int newCapacity) {
    if (newCapacity <= entryCapacity_) {
        return;
    }
    HistoryEntry* newEntries = new HistoryEntry[newCapacity];
    for (int i = 0; i < entrySize_; ++i) {
        newEntries[i] = entries_[i];
    }
    delete[] entries_;
    entries_ = newEntries;
    entryCapacity_ = newCapacity;
}

// Расширение массива ключей позиций
void GameHistory::reservePositions(int newCapacity) {
    if (newCapacity <= positionCapacity_) {
        return;
    }
    std::string* newKeys = new std::string[newCapacity];
    for (int i = 0; i < positionSize_; ++i) {
        newKeys[i] = positionKeys_[i];
    }
    delete[] positionKeys_;
    positionKeys_ = newKeys;
    positionCapacity_ = newCapacity;
}

// Добавить ход в журнал
void GameHistory::addMove(const Move& move, int fullMoveNumber) {
    if (entrySize_ == entryCapacity_) {
        reserveEntries(entryCapacity_ == 0 ? 16 : entryCapacity_ * 2);
    }
    entries_[entrySize_].moveNumber = fullMoveNumber;
    entries_[entrySize_].player = move.player;
    entries_[entrySize_].move = move;
    ++entrySize_;
}

// Зафиксировать ключ позиции
void GameHistory::recordPosition(const std::string& positionKey) {
    if (positionSize_ == positionCapacity_) {
        reservePositions(positionCapacity_ == 0 ? 32 : positionCapacity_ * 2);
    }
    positionKeys_[positionSize_] = positionKey;
    ++positionSize_;
}

// Сколько раз встречалась позиция
int GameHistory::countPosition(const std::string& positionKey) const {
    int count = 0;
    for (int i = 0; i < positionSize_; ++i) {
        if (positionKeys_[i] == positionKey) {
            ++count;
        }
    }
    return count;
}

// Число записанных ходов
int GameHistory::size() const { return entrySize_; }

// Доступ к записи по индексу
const HistoryEntry& GameHistory::getEntry(int index) const { return entries_[index]; }

// Текстовый вывод всей истории
std::string GameHistory::formatAll() const {
    std::ostringstream out;
    out << "=== Game History ===\n";
    for (int i = 0; i < entrySize_; ++i) {
        const HistoryEntry& e = entries_[i];
        out << e.moveNumber << ". " << colorToString(e.player) << ": "
            << pieceTypeToString(e.move.pieceType) << " "
            << squareName(e.move.from.row, e.move.from.col) << " -> "
            << squareName(e.move.to.row, e.move.to.col);
        if (e.move.isCapture) {
            out << " (capture " << pieceTypeToString(e.move.capturedType) << ")";
        }
        if (e.move.isPromotion) {
            out << " (promotion to " << pieceTypeToString(e.move.promotionTo) << ")";
        }
        out << '\n';
    }
    return out.str();
}
