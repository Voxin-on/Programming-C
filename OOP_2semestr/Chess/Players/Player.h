#ifndef PLAYER_H
#define PLAYER_H

#include "Core/ChessTypes.h"

class Board;
struct Move;

// Абстрактный игрок (полиморфизм).
class Player {
public:
    explicit Player(Color color);
    virtual ~Player();

    Player(const Player& other);
    Player& operator=(const Player& other);

    Color getColor() const;
    // Запрос следующего хода; false — отказ или конец ходов.
    virtual bool requestMove(Board& board, Move& outMove) = 0;
    // Имя для отображения в интерфейсе.
    virtual const char* getName() const = 0;
    // Разрешён ли повтор ввода после неправильного хода.
    virtual bool allowsRetryOnIllegalMove() const;

protected:
    Color color_;
};

#endif
