#include "Players/PlayerInput.h"

#include <cctype>
#include <iostream>

// Виртуальный деструктор интерфейса по умолчанию.
IPlayerInput::~IPlayerInput() = default;

// Разбор клетки вида e2 в координаты доски.
bool ConsolePlayerInput::parseSquare(const std::string& text, int& row, int& col) {
    if (text.size() != 2) {
        return false;
    }
    const char file = static_cast<char>(std::tolower(text[0]));
    const char rank = text[1];
    // Файл a–h, вертикаль 1–8.
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        return false;
    }
    col = file - 'a';
    row = 8 - (rank - '0');
    return true;
}

// Символ Q/R/B/N в тип фигуры превращения.
PieceType ConsolePlayerInput::parsePromotionChar(char ch) {
    switch (std::toupper(ch)) {
        case 'Q': return PieceType::Queen;
        case 'R': return PieceType::Rook;
        case 'B': return PieceType::Bishop;
        case 'N': return PieceType::Knight;
        default: return PieceType::None;
    }
}

// Чтение хода из консоли (from to); false при quit/exit или ошибке.
bool ConsolePlayerInput::readMove(Board& board, Color color, Move& outMove,
                                 std::string& errorMessage) {
    (void)board;
    std::cout << (color == Color::White ? "White" : "Black")
              << " move (example: e2 e4): ";

    std::string fromText;
    std::string toText;
    if (!(std::cin >> fromText >> toText)) {
        errorMessage = "Input error. Try again.";
        std::cout << errorMessage << '\n';
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }

    Move m;
    m.player = color;
    // Выход из игры по ключевым словам.
    if (fromText == "quit" || fromText == "exit") {
        errorMessage = "Quit requested.";
        return false;
    }

    if (!parseSquare(fromText, m.from.row, m.from.col) ||
        !parseSquare(toText, m.to.row, m.to.col)) {
        errorMessage = "Invalid square format. Use format like e2 e4.";
        std::cout << errorMessage << '\n';
        return false;
    }

    m.isPromotion = false;
    m.promotionTo = PieceType::Queen;
    m.isCapture = false;
    m.capturedType = PieceType::None;
    m.pieceType = PieceType::None;

    outMove = m;
    errorMessage.clear();
    return true;
}

// Запрос символа превращения; при ошибке — ферзь.
PieceType ConsolePlayerInput::readPromotionChoice(Color color) {
    (void)color;
    std::cout << "Pawn promotion — choose piece: Q=Queen, R=Rook, B=Bishop, N=Knight: ";
    char ch = 'Q';
    std::cin >> ch;
    const PieceType choice = parsePromotionChar(ch);
    if (choice != PieceType::None) {
        return choice;
    }
    std::cout << "Unknown choice, Queen selected.\n";
    return PieceType::Queen;
}
