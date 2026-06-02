#ifndef BOARD_H
#define BOARD_H

#include "Core/ChessTypes.h"

#include <string>
#include <vector>

class Piece;

enum class GameStatus {
    InProgress,
    Check,
    Checkmate,
    Stalemate,
    DrawFiftyMove,
    DrawThreefoldRepetition
};

class Board {
public:
    // конструктор начальной позиции
    Board();
    // конструктор загрузки из файла
    explicit Board(const std::string& filePath);
    // деструктор
    ~Board();

    // false, если файл не открылся или формат неверный
    bool isPositionLoaded() const;

    // копирующий конструктор
    Board(const Board& other);
    // оператор присваивания
    Board& operator=(const Board& other);

    // сброс в начальную позицию
    void resetToStartingPosition();
    // очистка доски
    void clear();

    // фигура на клетке
    Piece* getPiece(int row, int col) const;
    // установить фигуру на клетку
    void setPiece(int row, int col, Piece* piece);

    // чей сейчас ход
    Color getActiveColor() const;
    // задать активный цвет
    void setActiveColor(Color color);

    // цель взятия на проходе
    Position getEnPassantTarget() const;
    // атакована ли клетка
    bool isSquareAttacked(int row, int col, Color byColor) const;
    // король под шахом
    bool isKingInCheck(Color kingColor) const;

    // легален ли ход
    bool isLegalMove(const Move& move);
    // все легальные ходы стороны
    std::vector<Move> generateLegalMoves(Color color);

    // выполнить ход
    MoveUndo makeMove(const Move& move);
    // отменить ход
    void unmakeMove(const MoveUndo& undo);

    // статус партии
    GameStatus getGameStatus();
    // ASCII-представление доски
    std::string toAscii() const;
    // ключ позиции для повторов
    std::string getPositionKey() const;

    // счётчик полуходов без взятий и пешечных ходов
    int getHalfMoveClock() const;
    // ничья по правилу 50 ходов
    bool isFiftyMoveRuleDraw() const;

    // свободен ли путь между клетками
    bool isPathClear(int fromRow, int fromCol, int toRow, int toCol) const;

    // безопасен ли путь короля при рокировке
    bool isCastlingPathSafe(int row, int fromCol, int toCol, Color kingColor) const;

    // проверка доски для файла
    bool isPositionValid() const;

private:
    Piece* squares_[8][8];
    Color activeColor_;
    Position enPassantTarget_;
    bool enPassantValid_;
    int halfMoveClock_;
    int fullMoveNumber_;

    // удалить все фигуры с доски
    void destroyAllPieces();
    // скопировать фигуры с другой доски
    void copyFrom(const Board& other);
    // загрузить позицию из текстового файла
    bool loadFromTextFile(const std::string& filePath);

    bool positionLoadedOk_;
    // оставит ли ход короля под шахом
    bool wouldLeaveKingInCheck(const Move& move);
    // найти короля на доске
    void findKing(Color color, int& row, int& col) const;
};

#endif
