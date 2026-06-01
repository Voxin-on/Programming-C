#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include "Core/Board.h"
#include "Core/ChessTypes.h"

#include <string>

// Интерфейс ввода для HumanPlayer (без привязки к конкретному UI).
class IPlayerInput {
public:
    virtual ~IPlayerInput();

    // Чтение хода; errorMessage — текст ошибки формата.
    virtual bool readMove(Board& board, Color color, Move& outMove,
                          std::string& errorMessage) = 0;
    // Выбор фигуры при превращении пешки.
    virtual PieceType readPromotionChoice(Color color) = 0;
};

// Консольный ввод (cin/cout только здесь).
class ConsolePlayerInput : public IPlayerInput {
public:
    bool readMove(Board& board, Color color, Move& outMove,
                  std::string& errorMessage) override;
    PieceType readPromotionChoice(Color color) override;

private:
    // Разбор клетки вида e2 в координаты доски.
    static bool parseSquare(const std::string& text, int& row, int& col);
    // Символ Q/R/B/N в тип фигуры превращения.
    static PieceType parsePromotionChar(char ch);
};

#endif
