#ifndef CONSOLE_PRESENTER_H
#define CONSOLE_PRESENTER_H

#include "Core/ChessGame.h"

#include <iostream>
#include <string>

class ConsoleUiCallbacks : public IGameUiCallbacks {
public:
    // Выводит предупреждение игры в консоль.
    void onWarning(const std::string& message) override;
};

// Слой представления (UI), отделённый от игровой логики.
class ConsolePresenter {
public:
    // Печатает ASCII-доску.
    static void printBoard(const Board& board);
    // Заголовок текущего хода.
    static void printTurnHeader(const Player& player);
    // Результат применения хода.
    static void printTurnResult(const TurnResult& result);
    // Полная история партии.
    static void printHistory(const GameHistory& history);
    // Одна строка текста в консоль.
    static void printLine(const std::string& text);
    // Справка по командам ввода.
    static void printHelp();
};

#endif
