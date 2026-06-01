#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "Core/Board.h"
#include "Core/GameHistory.h"
#include "Players/Player.h"

#include <string>

class IGameUiCallbacks {
public:
    // виртуальный деструктор колбэков UI
    virtual ~IGameUiCallbacks();
    // показать предупреждение в интерфейсе
    virtual void onWarning(const std::string& message) = 0;
};

struct TurnResult {
    bool success;
    bool gameOver;
    Move move;
    GameStatus status;
    std::string message;
};

// Контроллер партии. Не выполняет ввод-вывод (кроме опциональных колбэков).
class ChessGame {
public:
    // инициализация партии и игроков
    ChessGame(Player* whitePlayer, Player* blackPlayer);
    // освободить ресурсы контроллера
    ~ChessGame();

    ChessGame(const ChessGame& other) = delete;
    ChessGame& operator=(const ChessGame& other) = delete;

    // подключить колбэки UI
    void setUiCallbacks(IGameUiCallbacks* callbacks);

    // доступ к доске
    Board& getBoard();
    // история ходов и позиций
    const GameHistory& getHistory() const;
    // чей сейчас ход
    Player* getCurrentPlayer() const;
    // статус партии (мат, пат, ничья и т.д.)
    GameStatus getStatus();
    // завершена ли партия
    bool isGameOver();
    // число полуходов с начала игры
    int getPlyCount() const;

    // выполнить один ход текущего игрока
    TurnResult playTurn();

    // заменить доску позицией из файла; сбросить историю и счётчик ходов
    bool loadPosition(const std::string& filePath);

private:
    Board board_;
    Player* whitePlayer_;
    Player* blackPlayer_;
    Player* currentPlayer_;
    GameHistory history_;
    IGameUiCallbacks* uiCallbacks_;
    int plyCount_;
    bool drawDeclared_;
    GameStatus drawStatus_;

    // передать ход сопернику
    void switchTurn();
    // заполнить тип фигуры и взятие в Move
    void finalizeMoveMetadata(Move& move) const;
    // проверить правило 50 ходов и троекратное повторение
    GameStatus checkDrawConditions();
    // текстовое сообщение по статусу
    std::string buildStatusMessage(GameStatus status) const;
    // мат, пат или объявленная ничья
    bool isTerminalStatus(GameStatus status) const;
};

#endif
