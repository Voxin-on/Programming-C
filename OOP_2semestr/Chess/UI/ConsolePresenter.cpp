#include "UI/ConsolePresenter.h"

namespace {

// Клетка в нотации a1..h8.
std::string squareName(const Position& pos) {
    const char file = static_cast<char>('a' + pos.col);
    const char rank = static_cast<char>('1' + (7 - pos.row));
    return std::string(1, file) + std::string(1, rank);
}

}  // namespace

// Показывает предупреждение от ChessGame в консоли.
void ConsoleUiCallbacks::onWarning(const std::string& message) {
    std::cout << "[!] " << message << '\n' << std::flush;
}

// Выводит текущую позицию в ASCII.
void ConsolePresenter::printBoard(const Board& board) {
    std::cout << board.toAscii() << '\n';
}

// Печатает имя и цвет игрока перед ходом.
void ConsolePresenter::printTurnHeader(const Player& player) {
    std::cout << "\n--- " << player.getName() << " (" << colorToString(player.getColor())
              << ") ---\n"
              << std::flush;
}

// Сообщает об успехе или ошибке хода.
void ConsolePresenter::printTurnResult(const TurnResult& result) {
    if (result.success) {  // Ход применён — координаты и статус
        std::cout << "Move: " << squareName(result.move.from) << " -> "
                  << squareName(result.move.to) << ". Status: " << result.message << '\n'
                  << std::flush;
    } else {  // Ход отклонён — показать причину
        std::cout << "Turn failed: " << result.message << '\n' << std::flush;
    }
}

// Выводит отформатированную историю ходов.
void ConsolePresenter::printHistory(const GameHistory& history) {
    std::cout << history.formatAll() << '\n';
}

// Печатает строку с немедленным сбросом буфера.
void ConsolePresenter::printLine(const std::string& text) {
    std::cout << text << '\n' << std::flush;
}

// Выводит краткую справку по синтаксису ходов.
void ConsolePresenter::printHelp() {
    printLine("Commands: enter move as [from] [to], e.g. e2 e4");
    printLine("Pawn promotion: Q/R/B/N when asked.");
    printLine("Type 'quit' as from-square to exit.");
}
