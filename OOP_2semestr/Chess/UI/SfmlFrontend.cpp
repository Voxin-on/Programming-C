#include "UI/SfmlFrontend.h"

#include "Pieces/Piece.h"

#include <cmath>
#include <optional>

namespace {

// Название типа фигуры для диалога превращения.
const char* pieceLabel(PieceType type) {
    switch (type) {
        case PieceType::Queen: return "Queen";
        case PieceType::Rook: return "Rook";
        case PieceType::Bishop: return "Bishop";
        case PieceType::Knight: return "Knight";
        default: return "Piece";
    }
}

// Символ фигуры для отрисовки; '?' если клетка пуста.
char pieceSymbol(const Piece* piece) {
    if (piece == nullptr) {  // Пустая клетка
        return '?';
    }
    return piece->getSymbol();
}

}  // namespace

// --- SfmlPlayerInput ---
// Сохраняет указатель на окно для ввода.
SfmlPlayerInput::SfmlPlayerInput(SfmlFrontend* frontend) : frontend_(frontend) {}

// Делегирует ожидание хода окну SFML.
bool SfmlPlayerInput::readMove(Board& board, Color color, Move& outMove,
                               std::string& errorMessage) {
    (void)errorMessage;
    if (frontend_ == nullptr) {  // Нет привязки к окну
        return false;
    }
    return frontend_->waitForMove(board, color, outMove);
}

// Запрашивает выбор фигуры при превращении пешки.
PieceType SfmlPlayerInput::readPromotionChoice(Color color) {
    if (frontend_ == nullptr) {  // Без окна — ферзь по умолчанию
        return PieceType::Queen;
    }
    return frontend_->waitForPromotion(color);
}

// --- SfmlUiCallbacks ---
// Сохраняет указатель на окно для колбэков.
SfmlUiCallbacks::SfmlUiCallbacks(SfmlFrontend* frontend) : frontend_(frontend) {}

// Передаёт предупреждение в GUI и обновляет кадр.
void SfmlUiCallbacks::onWarning(const std::string& message) {
    if (frontend_ != nullptr) {  // Обновляем экран только при живом окне
        frontend_->setWarning(message);
        frontend_->pumpFrame();
    }
}

// --- SfmlFrontend ---
// Инициализация окна, шрифта и состояния ввода.
SfmlFrontend::SfmlFrontend()
    : window_(sf::VideoMode({820, 660}), "Chess"),
      fontLoaded_(false),
      closed_(false),
      inputMode_(InputMode::Move),
      inputColor_(Color::White),
      moveReady_(false),
      promotionReady_(false),
      pendingPromotion_(PieceType::Queen),
      hasSelection_(false),
      selectedFrom_(-1, -1) {
    window_.setFramerateLimit(60);
    fontLoaded_ = loadFont();
}

// Деструктор по умолчанию.
SfmlFrontend::~SfmlFrontend() = default;

// Пробует загрузить шрифт из списка путей Windows.
bool SfmlFrontend::loadFont() {
    const char* paths[] = {"C:/Windows/Fonts/arial.ttf", "C:/Windows/Fonts/segoeui.ttf",
                           "arial.ttf"};
    for (const char* path : paths) {
        if (font_.openFromFile(path)) {  // Первый успешный путь
            return true;
        }
    }
    return false;
}

// Окно SFML открыто и не помечено закрытым.
bool SfmlFrontend::isOpen() const { return window_.isOpen() && !closed_; }

// Помечает окно закрытым и вызывает close().
void SfmlFrontend::close() {
    closed_ = true;
    window_.close();
}

// Устанавливает текст баннера.
void SfmlFrontend::setBanner(const std::string& text) { banner_ = text; }

// Устанавливает текст предупреждения.
void SfmlFrontend::setWarning(const std::string& text) { warning_ = text; }

// Очищает строку предупреждения.
void SfmlFrontend::clearWarning() { warning_.clear(); }

// Координаты левого верхнего угла клетки на экране.
sf::Vector2f SfmlFrontend::squareTopLeft(int row, int col) const {
    return sf::Vector2f(static_cast<float>(kBoardX + col * kCellSize),
                        static_cast<float>(kBoardY + row * kCellSize));
}

// Преобразует пиксели экрана в индексы клетки 0..7.
bool SfmlFrontend::screenToSquare(int x, int y, int& row, int& col) const {
    const int localX = x - kBoardX;
    const int localY = y - kBoardY;
    if (localX < 0 || localY < 0) {  // Клик вне области доски
        return false;
    }
    col = localX / kCellSize;
    row = localY / kCellSize;
    return col >= 0 && col < 8 && row >= 0 && row < 8;  // Клетка внутри 8×8
}

// Заполняет legalTargets_ ходами с выбранной клетки.
void SfmlFrontend::updateLegalTargets(Board& board, Color color, int fromRow,
                                      int fromCol) {
    legalTargets_.clear();
    const std::vector<Move> moves = board.generateLegalMoves(color);
    for (const Move& m : moves) {
        if (m.from.row == fromRow && m.from.col == fromCol) {  // Ход с выбранной клетки
            legalTargets_.push_back(m.to);
        }
    }
}

// Обрабатывает клик по кнопке Q/R/B/N в диалоге превращения.
void SfmlFrontend::handlePromotionClick(int x, int y) {
    const int bx = 210;
    const int by = 280;
    const int bw = 90;
    const int bh = 44;
    const int gap = 10;
    const PieceType options[] = {PieceType::Queen, PieceType::Rook, PieceType::Bishop,
                                 PieceType::Knight};
    for (int i = 0; i < 4; ++i) {
        const int left = bx + i * (bw + gap);
        if (x >= left && x <= left + bw && y >= by && y <= by + bh) {  // Попадание в кнопку i
            pendingPromotion_ = options[i];
            promotionReady_ = true;
            return;
        }
    }
}

// Двухшаговый выбор хода: фигура, затем клетка назначения.
void SfmlFrontend::handleBoardClick(int row, int col, Board& board) {
    const Piece* piece = board.getPiece(row, col);

    if (!hasSelection_) {  // Первый клик — выбор своей фигуры
        if (piece == nullptr || piece->getColor() != inputColor_) {  // Не своя фигура
            return;
        }
        hasSelection_ = true;
        selectedFrom_ = Position(row, col);
        updateLegalTargets(board, inputColor_, row, col);
        return;
    }

    if (selectedFrom_.row == row && selectedFrom_.col == col) {  // Повторный клик — снять выбор
        hasSelection_ = false;
        legalTargets_.clear();
        return;
    }

    Move m;
    m.from = selectedFrom_;
    m.to = Position(row, col);
    m.player = inputColor_;
    m.isPromotion = false;
    m.promotionTo = PieceType::Queen;
    pendingMove_ = m;
    moveReady_ = true;

    hasSelection_ = false;
    legalTargets_.clear();
}

// Разбор закрытия окна, Esc и кликов мыши.
void SfmlFrontend::handleEvent(const sf::Event& event, Board& board) {
    if (event.is<sf::Event::Closed>()) {  // Крестик окна
        close();
        return;
    }

    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
        if (key->code == sf::Keyboard::Key::Escape) {  // Выход по Esc
            close();
        }
    }

    if (const auto* click = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (click->button != sf::Mouse::Button::Left) {  // Только левая кнопка
            return;
        }
        const int x = click->position.x;
        const int y = click->position.y;

        if (inputMode_ == InputMode::Promotion) {  // Режим выбора превращения
            handlePromotionClick(x, y);
            return;
        }

        int row = -1;
        int col = -1;
        if (screenToSquare(x, y, row, col)) {  // Клик по доске
            handleBoardClick(row, col, board);
        }
    }
}

// Обрабатывает события и рисует минимальный кадр (баннер/предупреждение).
bool SfmlFrontend::pumpFrame() {
    if (!isOpen()) {  // Окно уже закрыто
        return false;
    }

    while (const std::optional event = window_.pollEvent()) {
        handleEvent(*event, displayBoard_);
    }

    window_.clear(sf::Color(45, 45, 48));
    drawText("Chess", 24, 16, 22, sf::Color::White);
    if (!banner_.empty()) {  // Баннер под заголовком
        drawText(banner_, 24, 40, 16, sf::Color(200, 200, 200));
    }
    if (!warning_.empty()) {  // Строка предупреждения внизу
        drawText(warning_, 24, 620, 16, sf::Color(255, 180, 80));
    }
    window_.display();
    return isOpen();
}

// Рисует шахматную сетку из светлых и тёмных клеток.
void SfmlFrontend::drawBoard(const Board& board) {
    (void)board;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            sf::RectangleShape cell(
                sf::Vector2f(static_cast<float>(kCellSize), static_cast<float>(kCellSize)));
            cell.setPosition(squareTopLeft(r, c));
            const bool light = (r + c) % 2 == 0;  // Шахматная раскраска клетки
            cell.setFillColor(light ? sf::Color(240, 217, 181) : sf::Color(181, 136, 99));
            window_.draw(cell);
        }
    }
}

// Подсвечивает выбранную клетку и возможные ходы.
void SfmlFrontend::drawHighlights() {
    if (hasSelection_) {  // Жёлтая подсветка выбранной фигуры
        sf::RectangleShape sel(
            sf::Vector2f(static_cast<float>(kCellSize), static_cast<float>(kCellSize)));
        sel.setPosition(squareTopLeft(selectedFrom_.row, selectedFrom_.col));
        sel.setFillColor(sf::Color(255, 255, 100, 90));
        window_.draw(sel);
    }

    for (const Position& p : legalTargets_) {
        sf::CircleShape dot(10.0f);
        dot.setFillColor(sf::Color(60, 180, 75, 180));
        const sf::Vector2f tl = squareTopLeft(p.row, p.col);
        dot.setPosition({tl.x + kCellSize / 2.0f - 10.0f, tl.y + kCellSize / 2.0f - 10.0f});
        window_.draw(dot);
    }
}

// Отрисовывает символы всех фигур на доске.
void SfmlFrontend::drawPieces(const Board& board) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            const Piece* piece = board.getPiece(r, c);
            if (piece == nullptr) {  // Пустая клетка — пропуск
                continue;
            }
            if (!fontLoaded_) {  // Без шрифта символы не рисуем
                continue;
            }
            sf::Text label(font_, std::string(1, pieceSymbol(piece)), 42);
            label.setFillColor(piece->getColor() == Color::White ? sf::Color::White
                                                                 : sf::Color(30, 30, 30));  // Цвет по стороне
            label.setOutlineThickness(1.5f);
            label.setOutlineColor(sf::Color::Black);
            const sf::Vector2f tl = squareTopLeft(r, c);
            label.setPosition({tl.x + 20.0f, tl.y + 10.0f});
            window_.draw(label);
        }
    }
}

// Выводит строку текста, если шрифт загружен.
void SfmlFrontend::drawText(const std::string& text, float x, float y, unsigned int size,
                            sf::Color color) {
    if (!fontLoaded_) {  // Без шрифта текст не рисуется
        return;
    }
    sf::Text label(font_, text, size);
    label.setFillColor(color);
    label.setPosition({x, y});
    window_.draw(label);
}

// Рисует боковую панель: ход, статус, управление.
void SfmlFrontend::drawPanel(const Board& board, Color sideToMove,
                             const std::string& statusLine) {
    float y = static_cast<float>(kBoardY);
    drawText("Side panel", static_cast<float>(kPanelX), y, 18, sf::Color::White);
    y += 28;
    drawText("To move: " + colorToString(sideToMove), static_cast<float>(kPanelX), y, 16,
             sf::Color(220, 220, 220));
    y += 26;
    drawText("Status: " + statusLine, static_cast<float>(kPanelX), y, 16, sf::Color(220, 220, 220));
    y += 26;
    drawText("Halfmove clock: " + std::to_string(board.getHalfMoveClock()),
             static_cast<float>(kPanelX), y, 14, sf::Color(180, 180, 180));
    y += 40;
    drawText("Controls:", static_cast<float>(kPanelX), y, 16, sf::Color::White);
    y += 22;
    drawText("Click piece, then cell", static_cast<float>(kPanelX), y, 14,
             sf::Color(180, 180, 180));
    y += 20;
    drawText("Esc — quit", static_cast<float>(kPanelX), y, 14, sf::Color(180, 180, 180));
}

// Модальный диалог выбора фигуры при превращении пешки.
void SfmlFrontend::drawPromotionDialog(Color color) {
    sf::RectangleShape overlay(sf::Vector2f(820.0f, 660.0f));
    overlay.setFillColor(sf::Color(0, 0, 0, 160));
    window_.draw(overlay);

    drawText("Pawn promotion (" + colorToString(color) + ")", 250, 240, 20, sf::Color::White);

    const PieceType options[] = {PieceType::Queen, PieceType::Rook, PieceType::Bishop,
                                 PieceType::Knight};
    const char* labels[] = {"Q", "R", "B", "N"};
    const int bx = 210;
    const int by = 280;
    const int bw = 90;
    const int bh = 44;
    const int gap = 10;

    for (int i = 0; i < 4; ++i) {
        sf::RectangleShape btn(sf::Vector2f(static_cast<float>(bw), static_cast<float>(bh)));
        btn.setPosition({static_cast<float>(bx + i * (bw + gap)), static_cast<float>(by)});
        btn.setFillColor(sf::Color(70, 110, 170));
        btn.setOutlineThickness(1.0f);
        btn.setOutlineColor(sf::Color::White);
        window_.draw(btn);
        drawText(std::string(labels[i]) + " — " + pieceLabel(options[i]),
                 static_cast<float>(bx + 8 + i * (bw + gap)), static_cast<float>(by + 12), 14,
                 sf::Color::White);
    }
}

// Полный кадр: события, доска, панель, диалог превращения.
void SfmlFrontend::draw(const Board& board, Color sideToMove, const std::string& statusLine) {
    if (!isOpen()) {  // Окно закрыто — не рисуем
        return;
    }

    displayBoard_ = board;

    while (const std::optional event = window_.pollEvent()) {
        handleEvent(*event, displayBoard_);
    }

    window_.clear(sf::Color(45, 45, 48));
    drawText("Chess", 24, 16, 22, sf::Color::White);
    if (!banner_.empty()) {  // Баннер под заголовком
        drawText(banner_, 24, 40, 16, sf::Color(200, 200, 200));
    }
    if (!warning_.empty()) {  // Строка предупреждения внизу
        drawText(warning_, 24, 630, 16, sf::Color(255, 180, 80));
    }

    drawBoard(displayBoard_);
    drawHighlights();
    drawPieces(displayBoard_);
    drawPanel(displayBoard_, sideToMove, statusLine);

    if (inputMode_ == InputMode::Promotion) {  // Поверх доски — диалог превращения
        drawPromotionDialog(inputColor_);
    }

    window_.display();
}

// Обновляет баннер и перерисовывает доску во время хода ИИ.
void SfmlFrontend::drawThinking(const Board& board, const std::string& message) {
    setBanner(message);
    draw(board, board.getActiveColor(), message);
}

// Цикл ожидания: пользователь выбирает from/to кликами.
bool SfmlFrontend::waitForMove(Board& board, Color color, Move& outMove) {
    inputMode_ = InputMode::Move;
    inputColor_ = color;
    moveReady_ = false;
    hasSelection_ = false;
    legalTargets_.clear();
    clearWarning();

    while (isOpen()) {
        draw(board, color, "Your turn — select piece and destination");
        if (moveReady_) {  // Ход собран — вернуть вызывающему коду
            outMove = pendingMove_;
            moveReady_ = false;
            return true;
        }
    }
    return false;
}

// Цикл ожидания выбора Q/R/B/N после превращения.
PieceType SfmlFrontend::waitForPromotion(Color color) {
    inputMode_ = InputMode::Promotion;
    inputColor_ = color;
    promotionReady_ = false;

    while (isOpen()) {
        draw(displayBoard_, color, "Choose promotion piece");
        if (promotionReady_) {  // Фигура выбрана — выход из режима Promotion
            inputMode_ = InputMode::Move;
            return pendingPromotion_;
        }
    }
    inputMode_ = InputMode::Move;  // Окно закрыто — ферзь по умолчанию
    return PieceType::Queen;
}

// Финальный экран с итогом партии.
void SfmlFrontend::showEndScreen(ChessGame& game) {
    const std::string status = game.getBoard().toAscii();
    (void)status;
    setBanner("Game finish — " + std::string(game.isGameOver() ? "finished" : "stopped"));
    draw(game.getBoard(), game.getCurrentPlayer()->getColor(), "Press Esc to exit");
}

// Блокирует выполнение до закрытия окна пользователем.
void SfmlFrontend::waitUntilClosed() {
    while (isOpen()) {
        draw(displayBoard_, Color::White, "Game finished — Esc to exit");
    }
}
