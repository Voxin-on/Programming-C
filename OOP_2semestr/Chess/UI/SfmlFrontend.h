#ifndef SFML_FRONTEND_H
#define SFML_FRONTEND_H

#include "Core/Board.h"
#include "Core/ChessGame.h"
#include "Core/ChessTypes.h"
#include "Players/PlayerInput.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

class SfmlFrontend;

// Ввод с доски (клики мышью) — реализация IPlayerInput.
class SfmlPlayerInput : public IPlayerInput {
public:
    // Привязывает ввод к окну SFML.
    explicit SfmlPlayerInput(SfmlFrontend* frontend);

    // Ожидает ход пользователя кликами по доске.
    bool readMove(Board& board, Color color, Move& outMove,
                  std::string& errorMessage) override;
    // Ожидает выбор фигуры при превращении пешки.
    PieceType readPromotionChoice(Color color) override;

private:
    SfmlFrontend* frontend_;
};

// Предупреждения из ChessGame на экран.
class SfmlUiCallbacks : public IGameUiCallbacks {
public:
    // Привязывает колбэки к окну SFML.
    explicit SfmlUiCallbacks(SfmlFrontend* frontend);

    // Показывает предупреждение в GUI.
    void onWarning(const std::string& message) override;

private:
    SfmlFrontend* frontend_;
};

// Окно SFML: отрисовка доски и обработка кликов.
class SfmlFrontend {
public:
    // Создаёт окно и загружает шрифт.
    SfmlFrontend();
    ~SfmlFrontend();

    SfmlFrontend(const SfmlFrontend& other) = delete;
    SfmlFrontend& operator=(const SfmlFrontend& other) = delete;

    // Окно открыто и не закрыто пользователем.
    bool isOpen() const;
    // Закрывает окно программно.
    void close();

    // Текст баннера вверху экрана.
    void setBanner(const std::string& text);
    // Текст предупреждения внизу экрана.
    void setWarning(const std::string& text);
    // Сбрасывает предупреждение.
    void clearWarning();

    // Полная отрисовка доски и панели.
    void draw(const Board& board, Color sideToMove, const std::string& statusLine);
    // Отрисовка во время «размышления» ИИ.
    void drawThinking(const Board& board, const std::string& message);
    // Обрабатывает события и обновляет кадр без доски.
    bool pumpFrame();

    // Блокируется до выбора хода мышью.
    bool waitForMove(Board& board, Color color, Move& outMove);
    // Блокируется до выбора фигуры превращения.
    PieceType waitForPromotion(Color color);

    // Экран окончания партии.
    void showEndScreen(ChessGame& game);
    // Ждёт закрытия окна после игры.
    void waitUntilClosed();

private:
    enum class InputMode { Move, Promotion };

    sf::RenderWindow window_;
    sf::Font font_;
    bool fontLoaded_;
    bool closed_;

    InputMode inputMode_;
    Color inputColor_;
    bool moveReady_;
    bool promotionReady_;
    Move pendingMove_;
    PieceType pendingPromotion_;

    bool hasSelection_;
    Position selectedFrom_;
    std::vector<Position> legalTargets_;

    std::string banner_;
    std::string warning_;
    Board displayBoard_;

    static constexpr int kCellSize = 72;
    static constexpr int kBoardX = 24;
    static constexpr int kBoardY = 72;
    static constexpr int kPanelX = 620;

    // Загрузка системного шрифта из нескольких путей.
    bool loadFont();
    // Диспетчер SFML-событий (клавиши, клики, закрытие).
    void handleEvent(const sf::Event& event, Board& board);
    // Обработка клика по клетке доски.
    void handleBoardClick(int row, int col, Board& board);
    // Обработка клика по кнопкам превращения.
    void handlePromotionClick(int x, int y);
    // Список легальных целей для выбранной фигуры.
    void updateLegalTargets(Board& board, Color color, int fromRow, int fromCol);
    // Перевод координат экрана в индексы клетки.
    bool screenToSquare(int x, int y, int& row, int& col) const;
    // Левый верхний угол клетки в пикселях.
    sf::Vector2f squareTopLeft(int row, int col) const;

    // Рисует шахматную сетку.
    void drawBoard(const Board& board);
    // Подсветка выбранной фигуры и целей.
    void drawHighlights();
    // Символы фигур поверх клеток.
    void drawPieces(const Board& board);
    // Боковая панель со статусом партии.
    void drawPanel(const Board& board, Color sideToMove, const std::string& statusLine);
    // Диалог выбора фигуры при превращении.
    void drawPromotionDialog(Color color);
    // Вспомогательный вывод текста.
    void drawText(const std::string& text, float x, float y, unsigned int size,
                  sf::Color color);
};

#endif
