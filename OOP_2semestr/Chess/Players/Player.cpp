#include "Players/Player.h"

#include "Core/Board.h"

// Базовый конструктор: сохраняет цвет фигур игрока.
Player::Player(Color color) : color_(color) {}

// Виртуальный деструктор по умолчанию.
Player::~Player() = default;

// Копирование цвета из другого игрока.
Player::Player(const Player& other) : color_(other.color_) {}

// Присваивание цвета (защита от самоприсваивания).
Player& Player::operator=(const Player& other) {
    if (this != &other) {
        color_ = other.color_;
    }
    return *this;
}

// Возвращает цвет фигур этого игрока.
Color Player::getColor() const { return color_; }

// По умолчанию повтор хода после ошибки не нужен.
bool Player::allowsRetryOnIllegalMove() const { return false; }
