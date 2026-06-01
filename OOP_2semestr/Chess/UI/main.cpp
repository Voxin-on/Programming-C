#include "Core/ChessGame.h"
#include "Core/Board.h"
#include "Pieces/PieceFactory.h"
#include "UI/ConsolePresenter.h"
#include "AI/MinimaxAlphaBetaStrategy.h"
#include "Players/HumanPlayer.h"
#include "Players/AIPlayer.h"
#include "Players/PlayerInput.h"

#ifdef CHESS_WITH_SFML
#include "UI/SfmlFrontend.h"
#endif

#include <fstream>
#include <iostream>
#include <string>

namespace {

// Выводит справку по аргументам командной строки.
void printUsage(const char* program) {
    std::cout << "Usage:\n"
              << "  " << program << " console   Interactive console\n";
#ifdef CHESS_WITH_SFML
    std::cout << "  " << program << " gui       SFML window\n";
#else
    std::cout << "  (gui: rebuild with build_sfml.bat or CMake + SFML)\n";
#endif
}

// Проверяет, запрошен ли консольный режим.
bool isConsoleArg(const std::string& arg) {
    return arg == "console" || arg == "--console" || arg == "-c";
}

// Проверяет, запрошен ли GUI-режим.
bool isGuiArg(const std::string& arg) {
    return arg == "gui" || arg == "--gui" || arg == "-g";
}

// Считывает номер режима игры (1–4) из stdin.
bool readGameModeFromStdin(int& mode) {
    std::cout << "Select mode:\n"
              << "  1 - Human (White) vs AI (Black)\n"
              << "  2 - Human vs Human\n"
              << "  3 - Rule checks (console + out.txt)\n"
              << "  4 - AI vs AI from positions/sample.txt\n"
              << "Mode: ";
    if (!(std::cin >> mode)) {  // Ошибка ввода - режим не выбран
        return false;
    }
    return mode >= 1 && mode <= 4;
}

// Автоматические проверки правил (режим 3).

// Пишет строку одновременно в консоль и лог-файл.
void testLog(std::ostream& out, const std::string& line) {
    std::cout << line << '\n';
    out << line << '\n';
}

// Собирает объект хода для тестовых проверок.
Move testMove(int fromRow, int fromCol, int toRow, int toCol, Color side) {
    Move move;
    move.from = Position(fromRow, fromCol);
    move.to = Position(toRow, toCol);
    move.player = side;
    return move;
}

// Проверяет, разрешён ли ход для активной стороны.
bool testIsLegal(Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    Move move = testMove(fromRow, fromCol, toRow, toCol, board.getActiveColor());
    return board.isLegalMove(move);
}

// Применяет ход на доске, если он легален.
bool testPlay(Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    Move move = testMove(fromRow, fromCol, toRow, toCol, board.getActiveColor());
    if (!board.isLegalMove(move)) {  // Нелегальный ход не выполняем
        return false;
    }
    board.makeMove(move);
    return true;
}

// Фиксирует результат одной проверки правил (OK/FAIL).
void testCheck(std::ostream& out, const char* comment, bool ok, int& passed, int& total) {
    ++total;
    if (ok) {  // Успешная проверка увеличивает счётчик passed
        ++passed;
    }
    testLog(out, std::string(ok ? "OK  " : "FAIL") + " - " + comment);
}

// Ставит одну фигуру на пустую доску (после clear()).
void testPlace(Board& board, PieceType type, Color color, int row, int col) {
    board.setPiece(row, col, createPiece(type, color, row, col));
}

// Запускает набор автоматических проверок шахматных правил.
int runRuleChecks() {
    std::ofstream out("out.txt");
    if (!out) {  // Не удалось создать out.txt
        std::cerr << "Cannot write out.txt\n";
        return 1;
    }

    int passed = 0;
    int total = 0;

    testLog(out, "=== Chess rule checks ===");
    testLog(out, "");

    // Проверка: с начальной позиции e2-e4 разрешён
    {
        Board board;
        board.resetToStartingPosition();
        testCheck(out, "e2-e4 legal from start", testIsLegal(board, 6, 4, 4, 4), passed,
                  total);
    }

    // Проверка: пешка не ходит на 3 клетки вперёд
    {
        Board board;
        board.resetToStartingPosition();
        testCheck(out, "pawn cannot jump three squares", !testIsLegal(board, 6, 4, 3, 4),
                  passed, total);
    }

    // Проверка: рокировка с начальной позиции сразу невозможна (мешают фигуры)
    {
        Board board;
        board.resetToStartingPosition();
        testCheck(out, "castling blocked at start (pieces in way)",
                  !testIsLegal(board, 7, 4, 7, 6), passed, total);
    }

    // Загрузка позиции из текстового файла (формат: White: N / фигуры / Black: N / ...)
    {
        Board board("positions/sample.txt");
        testCheck(out, "position file loads (sample.txt)", board.isPositionLoaded(), passed,
                  total);
    }
    {
        Board board("positions/no_such_file.txt");
        testCheck(out, "missing position file fails", !board.isPositionLoaded(), passed, total);
    }

    // En passant
    {
        Board board;
        board.resetToStartingPosition();
        testPlay(board, 6, 4, 4, 4);   // e2-e4
        testPlay(board, 1, 3, 3, 3);   // d7-d5
        testCheck(out, "en passant capture legal",
                  testIsLegal(board, 4, 4, 3, 3), passed, total);
    }

    // Короткая рокировка: король e1, ладья h1, путь свободен
    {
        Board board;
        board.clear();
        testPlace(board, PieceType::King, Color::White, 7, 4);
        testPlace(board, PieceType::Rook, Color::White, 7, 7);
        board.setActiveColor(Color::White);
        testCheck(out, "white kingside castling legal (e1-g1)",
                  testIsLegal(board, 7, 4, 7, 6), passed, total);
    }

    // Рокировка запрещена: поле f1 под боем
    {
        Board board;
        board.clear();
        testPlace(board, PieceType::King, Color::White, 7, 4);
        testPlace(board, PieceType::Rook, Color::White, 7, 7);
        testPlace(board, PieceType::Rook, Color::Black, 7, 0);
        board.setActiveColor(Color::White);
        testCheck(out, "castling illegal through attacked f1",
                  !testIsLegal(board, 7, 4, 7, 6), passed, total);
    }

    // Длинная рокировка: король e1, ладья a1
    {
        Board board;
        board.clear();
        testPlace(board, PieceType::King, Color::White, 7, 4);
        testPlace(board, PieceType::Rook, Color::White, 7, 0);
        board.setActiveColor(Color::White);
        testCheck(out, "white queenside castling legal (e1-c1)",
                  testIsLegal(board, 7, 4, 7, 2), passed, total);
    }

    // Пат: король a8 заперт, шаха нет
    {
        Board board;
        board.clear();
        testPlace(board, PieceType::King, Color::Black, 0, 0);
        testPlace(board, PieceType::King, Color::White, 1, 2);
        testPlace(board, PieceType::Rook, Color::White, 1, 1);
        board.setActiveColor(Color::Black);
        testCheck(out, "stalemate detected", board.getGameStatus() == GameStatus::Stalemate,
                  passed, total);
    }

    // Шах: чёрный король под ударом ладьи
    {
        Board board;
        board.clear();
        testPlace(board, PieceType::King, Color::Black, 0, 4);
        testPlace(board, PieceType::Rook, Color::White, 7, 4);
        board.setActiveColor(Color::Black);
        testCheck(out, "check detected", board.getGameStatus() == GameStatus::Check, passed,
                  total);
    }

    testLog(out, "");
    testLog(out, "Result: " + std::to_string(passed) + " / " + std::to_string(total) +
                      " passed");
    testLog(out, "Full log saved to out.txt");

    return passed == total ? 0 : 1;  // 0 — все проверки пройдены
}

// Интерактивная консоль: режимы 1–2 (игра), 3 (тесты), 4 (AI vs AI из файла).
int runConsole() {
    ConsolePresenter::printLine("Chess");
    ConsolePresenter::printHelp();

    int mode = 1;
    if (!readGameModeFromStdin(mode)) {  // При ошибке ввода — режим по умолчанию
        mode = 1;
    }

    if (mode == 3) {  // Режим проверки правил без игры
        return runRuleChecks();
    }

    const char* positionFile = "positions/sample.txt";
    const int aiDepth = 4;
    const int maxPlies = 80;

    ConsolePlayerInput consoleInput;
    ConsoleUiCallbacks uiCallbacks;

    Player* white = nullptr;
    Player* black = nullptr;
    MinimaxAlphaBetaStrategy* strategy = nullptr;

    if (mode == 4) {  // Два ИИ, доска из файла
        ConsolePresenter::printLine("Mode 4: AI vs AI, board from " + std::string(positionFile) +
                                    " (depth " + std::to_string(aiDepth) + ")");
        MinimaxAlphaBetaStrategy* whiteStrategy = new MinimaxAlphaBetaStrategy(aiDepth);
        MinimaxAlphaBetaStrategy* blackStrategy = new MinimaxAlphaBetaStrategy(aiDepth);
        white = new AIPlayer(Color::White, whiteStrategy);
        black = new AIPlayer(Color::Black, blackStrategy);
    } else if (mode == 2) {  // Человек против человека
        white = new HumanPlayer(Color::White, &consoleInput);
        black = new HumanPlayer(Color::Black, &consoleInput);
    } else {  // Режим 1: человек против ИИ
        strategy = new MinimaxAlphaBetaStrategy(aiDepth);
        white = new HumanPlayer(Color::White, &consoleInput);
        black = new AIPlayer(Color::Black, strategy);
        strategy = nullptr;
    }

    ChessGame game(white, black);

    if (mode == 4) {
        if (!game.loadPosition(positionFile)) {
            ConsolePresenter::printLine("Cannot load position file (run from project root): " +
                                        std::string(positionFile));
            delete white;
            delete black;
            return 1;
        }
    } else {
        game.setUiCallbacks(&uiCallbacks);
    }

    ConsolePresenter::printBoard(game.getBoard());

    int ply = 0;
    while (!game.isGameOver()) {
        if (mode == 4 && ply >= maxPlies) {
            break;
        }

        ConsolePresenter::printTurnHeader(*game.getCurrentPlayer());
        const TurnResult result = game.playTurn();
        ConsolePresenter::printTurnResult(result);
        ConsolePresenter::printBoard(game.getBoard());

        if (!result.success) {
            break;
        }
        if (mode == 4) {
            ++ply;
        }
    }

    if (mode == 4 && ply >= maxPlies && !game.isGameOver()) {
        ConsolePresenter::printLine("Stopped: ply limit reached.");
    }

    ConsolePresenter::printLine("\n=== Game finish ===");
    if (mode == 4) {
        ConsolePresenter::printLine("Plies played: " + std::to_string(ply));
    } else {
        ConsolePresenter::printLine("Final status: " +
                                    std::string(game.isGameOver() ? "finished" : "stopped"));
    }
    ConsolePresenter::printHistory(game.getHistory());

    delete white;
    delete black;
    delete strategy;
    return 0;
}

#ifdef CHESS_WITH_SFML

// Преобразует статус партии в текст для панели GUI.
std::string statusToText(GameStatus status) {
    switch (status) {
        case GameStatus::Check:
            return "Check";
        case GameStatus::Checkmate:
            return "Checkmate";
        case GameStatus::Stalemate:
            return "Stalemate";
        case GameStatus::DrawFiftyMove:
            return "Draw (50-move rule)";
        case GameStatus::DrawThreefoldRepetition:
            return "Draw (threefold repetition)";
        default:
            return "In progress";
    }
}

// Определяет, ходит ли сейчас ИИ-игрок.
bool isAiTurn(const Player* player) {
    return dynamic_cast<const AIPlayer*>(player) != nullptr;
}

// Запускает игру человек против ИИ в SFML-окне.
int runSfml() {
    SfmlFrontend frontend;
    if (!frontend.isOpen()) {  // Окно не создано — выход с ошибкой
        return 1;
    }

    MinimaxAlphaBetaStrategy* strategy = new MinimaxAlphaBetaStrategy(4);
    SfmlPlayerInput sfmlInput(&frontend);
    SfmlUiCallbacks uiCallbacks(&frontend);

    HumanPlayer* white = new HumanPlayer(Color::White, &sfmlInput);
    AIPlayer* black = new AIPlayer(Color::Black, strategy);

    ChessGame game(white, black);
    game.setUiCallbacks(&uiCallbacks);

    frontend.setBanner("White (Human) vs Black (Minimax AI)");
    frontend.draw(game.getBoard(), Color::White, "Click a piece to start");

    while (frontend.isOpen() && !game.isGameOver()) {  // Цикл ходов, пока окно открыто
        Player* current = game.getCurrentPlayer();
        const std::string turnLine =
            std::string(current->getName()) + " (" + colorToString(current->getColor()) + ")";

        if (isAiTurn(current)) {  // Показываем индикатор «думает» для ИИ
            frontend.drawThinking(game.getBoard(), turnLine + " — thinking...");
        } else {  // Ожидаем клик пользователя
            frontend.draw(game.getBoard(), current->getColor(), turnLine);
        }

        const TurnResult result = game.playTurn();

        if (!result.success) {  // Ошибка хода — предупреждение и выход из цикла
            frontend.setWarning(result.message);
            frontend.draw(game.getBoard(), game.getCurrentPlayer()->getColor(), "Turn failed");
            break;
        }

        frontend.clearWarning();
        frontend.draw(game.getBoard(), game.getCurrentPlayer()->getColor(),
                      statusToText(result.status));
    }

    frontend.showEndScreen(game);
    frontend.waitUntilClosed();

    delete white;
    delete black;
    return 0;
}

#endif  // CHESS_WITH_SFML

}  // namespace

// Точка входа: разбор аргументов и запуск выбранного режима.
int main(int argc, char* argv[]) {
    if (argc < 2) {  // Нет аргумента — показать usage
        printUsage(argv[0]);
        return 1;
    }

    const std::string arg = argv[1];
    if (arg == "--help" || arg == "-h" || arg == "/?") {  // Запрос справки
        printUsage(argv[0]);
        return 0;
    }

    if (isConsoleArg(arg)) {  // Консольный режим
        return runConsole();
    }

    if (isGuiArg(arg)) {  // GUI-режим (если собран с SFML)
#ifdef CHESS_WITH_SFML
        return runSfml();
#else
        std::cerr << "GUI is not available in this build. Use build_sfml.bat or enable SFML in CMake.\n";
        return 1;
#endif
    }

    std::cerr << "Unknown option: " << arg << "\n";
    printUsage(argv[0]);
    return 1;
}
