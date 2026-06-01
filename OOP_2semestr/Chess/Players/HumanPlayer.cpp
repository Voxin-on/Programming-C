#include "Players/HumanPlayer.h"

#include "Core/Board.h"
#include "Pieces/Piece.h"
#include "Players/PlayerInput.h"

// Конструктор: привязка к источнику ввода.
HumanPlayer::HumanPlayer(Color color, IPlayerInput* input)
    : Player(color), input_(input) {}

// Деструктор по умолчанию.
HumanPlayer::~HumanPlayer() = default;

// Копирование ссылки на источник ввода.
HumanPlayer::HumanPlayer(const HumanPlayer& other) : Player(other), input_(other.input_) {}

// Присваивание базовой части и указателя на ввод.
HumanPlayer& HumanPlayer::operator=(const HumanPlayer& other) {
    if (this != &other) {
        Player::operator=(other);
        input_ = other.input_;
    }
    return *this;
}

// Проверка: пешка достигает последней горизонтали.
bool HumanPlayer::isPawnPromotionMove(Board& board, const Move& move) const {
    const Piece* piece = board.getPiece(move.from.row, move.from.col);
    if (piece == nullptr || piece->getType() != PieceType::Pawn) {
        return false;
    }
    // Белые — 8-я горизонталь, чёрные — 1-я.
    return (color_ == Color::White && move.to.row == 0) ||
           (color_ == Color::Black && move.to.row == 7);
}

// Запрос хода у ввода; при превращении — выбор фигуры.
bool HumanPlayer::requestMove(Board& board, Move& outMove) {
    if (input_ == nullptr) {
        return false;
    }

    std::string errorMessage;
    while (true) {
        if (!input_->readMove(board, color_, outMove, errorMessage)) {
            if (!errorMessage.empty() && input_ != nullptr) {
                // Ошибка формата ввода — повторить запрос координат.
                continue;
            }
            return false;
        }
        outMove.player = color_;

        if (isPawnPromotionMove(board, outMove)) {
            outMove.isPromotion = true;
            outMove.promotionTo = input_->readPromotionChoice(color_);
        } else {
            outMove.isPromotion = false;
            outMove.promotionTo = PieceType::Queen;
        }
        return true;
    }
}

// Имя игрока для вывода в интерфейсе.
const char* HumanPlayer::getName() const { return "Human"; }

// Человек может повторить ввод после неправильного хода.
bool HumanPlayer::allowsRetryOnIllegalMove() const { return true; }
