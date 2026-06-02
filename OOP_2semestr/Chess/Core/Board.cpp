#include "Core/Board.h"

#include "Pieces/Piece.h"
#include "Pieces/PieceFactory.h"

#include <cctype>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>

namespace {

// фигура принадлежит противнику
bool isEnemy(const Piece* piece, Color color) {
    return piece != nullptr && piece->getColor() != color;
}

// разбор алгебраической нотации клетки
bool parseAlgebraicSquare(const std::string& square, int& row, int& col) {
    if (square.size() != 2) {  // ровно два символа
        return false;
    }
    const char file = static_cast<char>(std::toupper(static_cast<unsigned char>(square[0])));
    const char rank = square[1];
    if (file < 'A' || file > 'H' || rank < '1' || rank > '8') {  // допустимые файл и ранг
        return false;
    }
    col = file - 'A';
    row = 8 - (rank - '0');
    return true;
}

// разбор символа фигуры в тип
bool parsePieceToken(char symbol, Color side, PieceType& type) {
    if (side == Color::Black && symbol == 'p') {  // чёрная пешка строчной p
        type = PieceType::Pawn;
        return true;
    }
    const char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(symbol)));
    switch (upper) {
        case 'P':
            type = PieceType::Pawn;
            return true;
        case 'R':
            type = PieceType::Rook;
            return true;
        case 'N':
            type = PieceType::Knight;
            return true;
        case 'B':
            type = PieceType::Bishop;
            return true;
        case 'Q':
            type = PieceType::Queen;
            return true;
        case 'K':
            type = PieceType::King;
            return true;
        default:
            return false;
    }
}

// прочитать число фигур стороны из файла
bool readSideCount(std::istream& in, const char* label, int& count) {
    std::string line;
    if (!std::getline(in, line)) {
        return false;
    }
    const std::string prefix = std::string(label) + ":";
    if (line.size() < prefix.size() + 1) {  // строка слишком короткая
        return false;
    }
    for (size_t i = 0; i < prefix.size(); ++i) {
        const char a = static_cast<char>(std::tolower(static_cast<unsigned char>(line[i])));
        const char b = static_cast<char>(std::tolower(static_cast<unsigned char>(prefix[i])));
        if (a != b) {  // метка не совпала
            return false;
        }
    }
    count = std::atoi(line.c_str() + static_cast<int>(prefix.size()));
    return count >= 0;
}

// поставить одну фигуру из строки файла
bool placePieceLine(Board& board, const std::string& line, Color side) {
    if (line.size() < 3) {  // минимум символ, клетка
        return false;
    }

    PieceType type = PieceType::None;
    if (!parsePieceToken(line[0], side, type)) {
        return false;
    }

    int row = -1;
    int col = -1;
    if (!parseAlgebraicSquare(line.substr(1), row, col)) {
        return false;
    }
    if (board.getPiece(row, col) != nullptr) {  // клетка уже занята
        return false;
    }

    Piece* piece = createPiece(type, side, row, col);
    if (piece == nullptr) {
        return false;
    }
    piece->setHasMoved(true);
    board.setPiece(row, col, piece);
    return true;
}

// прочитать и поставить все фигуры стороны
bool readSidePieces(std::istream& in, Board& board, Color side, int expectedCount) {
    for (int i = 0; i < expectedCount; ++i) {
        std::string line;
        if (!std::getline(in, line)) {
            return false;
        }
        if (!placePieceLine(board, line, side)) {
            return false;
        }
    }
    return true;
}

}  // namespace

// инициализация пустой доски и начальной позиции
Board::Board()
    : activeColor_(Color::White),
      enPassantTarget_(-1, -1),
      enPassantValid_(false),
      halfMoveClock_(0),
      fullMoveNumber_(1),
      positionLoadedOk_(true) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            squares_[r][c] = nullptr;
        }
    }
    resetToStartingPosition();
}

// инициализация доски с загрузкой из файла
Board::Board(const std::string& filePath)
    : activeColor_(Color::White),
      enPassantTarget_(-1, -1),
      enPassantValid_(false),
      halfMoveClock_(0),
      fullMoveNumber_(1),
      positionLoadedOk_(false) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            squares_[r][c] = nullptr;
        }
    }
    positionLoadedOk_ = loadFromTextFile(filePath);
}

// успешна ли загрузка позиции
bool Board::isPositionLoaded() const { return positionLoadedOk_; }

// загрузка позиции из текстового файла
bool Board::loadFromTextFile(const std::string& filePath) {
    clear();

    std::ifstream in(filePath.c_str());
    if (!in) {  // файл не открылся
        return false;
    }

    int whiteCount = 0;
    int blackCount = 0;
    if (!readSideCount(in, "White", whiteCount) || !readSidePieces(in, *this, Color::White, whiteCount)) {
        clear();
        return false;
    }
    if (!readSideCount(in, "Black", blackCount) || !readSidePieces(in, *this, Color::Black, blackCount)) {
        clear();
        return false;
    }

    if (!isPositionValid()) {
        clear();  // очищаем доску
        return false;
    }

    return true;
}

// деструктор
Board::~Board() { destroyAllPieces(); }

// копирующий конструктор
Board::Board(const Board& other)
    : activeColor_(other.activeColor_),
      enPassantTarget_(other.enPassantTarget_),
      enPassantValid_(other.enPassantValid_),
      halfMoveClock_(other.halfMoveClock_),
      fullMoveNumber_(other.fullMoveNumber_),
      positionLoadedOk_(other.positionLoadedOk_) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            squares_[r][c] = nullptr;
        }
    }
    copyFrom(other);
}

// оператор присваивания
Board& Board::operator=(const Board& other) {
    if (this != &other) {  // защита от самоприсваивания
        destroyAllPieces();
        activeColor_ = other.activeColor_;
        enPassantTarget_ = other.enPassantTarget_;
        enPassantValid_ = other.enPassantValid_;
        halfMoveClock_ = other.halfMoveClock_;
        fullMoveNumber_ = other.fullMoveNumber_;
        positionLoadedOk_ = other.positionLoadedOk_;
        copyFrom(other);
    }
    return *this;
}

// удалить все фигуры с доски
void Board::destroyAllPieces() {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            delete squares_[r][c];
            squares_[r][c] = nullptr;
        }
    }
}

// скопировать фигуры с другой доски
void Board::copyFrom(const Board& other) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (other.squares_[r][c] != nullptr) {  // клонировать занятую клетку
                squares_[r][c] = other.squares_[r][c]->clone();
            }
        }
    }
}

// очистить доску без начальной расстановки
void Board::clear() {
    destroyAllPieces();
    enPassantValid_ = false;
    halfMoveClock_ = 0;
    fullMoveNumber_ = 1;
    activeColor_ = Color::White;
}

// расставить стандартную начальную позицию
void Board::resetToStartingPosition() {
    clear();

    const PieceType backRank[] = {PieceType::Rook, PieceType::Knight, PieceType::Bishop,
                                  PieceType::Queen, PieceType::King, PieceType::Bishop,
                                  PieceType::Knight, PieceType::Rook};

    for (int c = 0; c < 8; ++c) {
        squares_[0][c] = createPiece(backRank[c], Color::Black, 0, c);
        squares_[1][c] = createPiece(PieceType::Pawn, Color::Black, 1, c);
        squares_[6][c] = createPiece(PieceType::Pawn, Color::White, 6, c);
        squares_[7][c] = createPiece(backRank[c], Color::White, 7, c);
    }
}

// получить фигуру на клетке
Piece* Board::getPiece(int row, int col) const {
    if (!Position(row, col).isOnBoard()) {  // координаты вне доски
        return nullptr;
    }
    return squares_[row][col];
}

// установить фигуру на клетку
void Board::setPiece(int row, int col, Piece* piece) {
    if (Position(row, col).isOnBoard()) {  // только для клеток доски
        squares_[row][col] = piece;
    }
}

// чей сейчас ход
Color Board::getActiveColor() const { return activeColor_; }
// задать активный цвет
void Board::setActiveColor(Color color) { activeColor_ = color; }

// вернуть цель en passant или (-1,-1)
Position Board::getEnPassantTarget() const {
    return enPassantValid_ ? enPassantTarget_ : Position(-1, -1);
}

// проверить свободность прямого пути
bool Board::isPathClear(int fromRow, int fromCol, int toRow, int toCol) const {
    const int dr = (toRow > fromRow) ? 1 : (toRow < fromRow ? -1 : 0);
    const int dc = (toCol > fromCol) ? 1 : (toCol < fromCol ? -1 : 0);
    int r = fromRow + dr;
    int c = fromCol + dc;
    while (r != toRow || c != toCol) {
        if (squares_[r][c] != nullptr) {  // преграда на пути
            return false;
        }
        r += dr;
        c += dc;
    }
    return true;
}

// найти координаты короля стороны
void Board::findKing(Color color, int& row, int& col) const {
    row = -1;
    col = -1;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            const Piece* p = squares_[r][c];
            if (p != nullptr && p->getType() == PieceType::King && p->getColor() == color) {
                row = r;
                col = c;
                return;
            }
        }
    }
}

// атакована ли клетка фигурами стороны
bool Board::isSquareAttacked(int row, int col, Color byColor) const {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            const Piece* p = squares_[r][c];
            if (p == nullptr || p->getColor() != byColor) {  // не наша фигура
                continue;
            }
            if (p->getType() == PieceType::Pawn) {
                const int dir = (byColor == Color::White) ? -1 : 1;
                if (r + dir == row && (c + 1 == col || c - 1 == col)) {  // пешка бьёт по диагонали
                    return true;
                }
            } else if (p->getType() == PieceType::King) {
                const int dr = std::abs(row - r);
                const int dc = std::abs(col - c);
                if (dr <= 1 && dc <= 1 && (dr + dc > 0)) {  // король рядом
                    return true;
                }
            } else if (p->isValidMove(*this, row, col)) {  // остальные фигуры
                return true;
            }
        }
    }
    return false;
}

// король стороны под шахом
bool Board::isKingInCheck(Color kingColor) const {
    int kr = -1, kc = -1;
    findKing(kingColor, kr, kc);
    if (kr < 0) {  // король не найден
        return false;
    }
    return isSquareAttacked(kr, kc, oppositeColor(kingColor));
}

// безопасен ли путь короля при рокировке
bool Board::isCastlingPathSafe(int row, int fromCol, int toCol, Color kingColor) const {
    const Color attacker = oppositeColor(kingColor);
    const int step = (toCol > fromCol) ? 1 : -1;
    for (int col = fromCol; col != toCol + step; col += step) {
        if (isSquareAttacked(row, col, attacker)) {  // клетка под атакой
            return false;
        }
    }
    return true;
}

// проверить ход пробным выполнением
bool Board::wouldLeaveKingInCheck(const Move& move) {
    Move full = move;
    const Piece* piece = getPiece(move.from.row, move.from.col);
    if (piece == nullptr) {  // нет фигуры на исходной клетке
        return true;
    }
    full.pieceType = piece->getType();
    const Piece* target = getPiece(move.to.row, move.to.col);
    full.isCapture = target != nullptr && target->getColor() != move.player;
    full.capturedType = full.isCapture ? target->getType() : PieceType::None;
    if (piece->getType() == PieceType::Pawn && !full.isCapture &&
        move.from.col != move.to.col) {  // возможное взятие на проходе
        const Position ep = getEnPassantTarget();
        if (ep.row == move.to.row && ep.col == move.to.col) {
            full.isCapture = true;
            full.capturedType = PieceType::Pawn;
        }
    }
    if (piece->getType() == PieceType::Pawn &&
        ((move.player == Color::White && move.to.row == 0) ||
         (move.player == Color::Black && move.to.row == 7))) {  // превращение пешки
        full.isPromotion = true;
        if (!isPromotionPiece(move.promotionTo)) {
            full.promotionTo = PieceType::Queen;
        } else {
            full.promotionTo = move.promotionTo;
        }
    }

    const MoveUndo undo = makeMove(full);
    const bool inCheck = isKingInCheck(move.player);
    unmakeMove(undo);
    return inCheck;
}

// проверить легальность хода
bool Board::isLegalMove(const Move& move) {
    if (!move.from.isOnBoard() || !move.to.isOnBoard()) {  // координаты вне доски
        return false;
    }

    Piece* piece = getPiece(move.from.row, move.from.col);
    if (piece == nullptr || piece->getColor() != move.player) {  // не наша фигура
        return false;
    }

    if (!piece->isValidMove(*this, move.to.row, move.to.col)) {  // правила фигуры
        return false;
    }

    const bool promotionRank =
        (piece->getType() == PieceType::Pawn) &&
        ((move.player == Color::White && move.to.row == 0) ||
         (move.player == Color::Black && move.to.row == 7));
    if (promotionRank) {  // нужна корректная фигура превращения
        if (!move.isPromotion || !isPromotionPiece(move.promotionTo)) {
            return false;
        }
    }

    const Piece* target = getPiece(move.to.row, move.to.col);
    if (target != nullptr && target->getColor() == move.player) {  // нельзя бить свою
        return false;
    }

    Move testMove = move;
    testMove.pieceType = piece->getType();
    return !wouldLeaveKingInCheck(testMove);
}

namespace {

// добавить ход, если он легален
void tryAddLegalMove(Board& board, std::vector<Move>& moves, int fr, int fc, int tr,
                     int tc, Color color) {
    if (!Position(tr, tc).isOnBoard()) {  // цель вне доски
        return;
    }
    const Piece* piece = board.getPiece(fr, fc);
    if (piece == nullptr) {
        return;
    }

    const bool promotionRank =
        (piece->getType() == PieceType::Pawn) &&
        ((color == Color::White && tr == 0) || (color == Color::Black && tr == 7));

    const PieceType promotionOptions[] = {PieceType::Queen, PieceType::Rook, PieceType::Bishop,
                                          PieceType::Knight};
    const int promotionCount = promotionRank ? 4 : 1;

    for (int pi = 0; pi < promotionCount; ++pi) {
        Move m;
        m.from = Position(fr, fc);
        m.to = Position(tr, tc);
        m.player = color;
        m.isPromotion = promotionRank;
        m.promotionTo = promotionRank ? promotionOptions[pi] : PieceType::Queen;
        if (!board.isLegalMove(m)) {  // пропустить нелегальный вариант
            continue;
        }
        const Piece* cap = board.getPiece(tr, tc);
        m.pieceType = piece->getType();
        m.isCapture = cap != nullptr && cap->getColor() != color;
        m.capturedType = m.isCapture ? cap->getType() : PieceType::None;
        moves.push_back(m);
    }
}

// добавить ходы по лучу до преграды
void addRayMoves(Board& board, std::vector<Move>& moves, int fr, int fc, Color color,
                 const int directions[][2], int dirCount) {
    for (int d = 0; d < dirCount; ++d) {
        int tr = fr + directions[d][0];
        int tc = fc + directions[d][1];
        while (Position(tr, tc).isOnBoard()) {
            tryAddLegalMove(board, moves, fr, fc, tr, tc, color);
            const Piece* target = board.getPiece(tr, tc);
            if (target != nullptr) {  // луч упёрся в фигуру
                break;
            }
            tr += directions[d][0];
            tc += directions[d][1];
        }
    }
}

}  // namespace

// сгенерировать все легальные ходы стороны
std::vector<Move> Board::generateLegalMoves(Color color) {
    std::vector<Move> moves;
    moves.reserve(40);

    static const int knightJumps[8][2] = {{2, 1},  {2, -1}, {-2, 1},  {-2, -1},
                                          {1, 2},  {1, -2},  {-1, 2},  {-1, -2}};
    static const int bishopDirs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    static const int rookDirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    static const int queenDirs[8][2] = {{1, 0},  {-1, 0}, {0, 1},  {0, -1},
                                        {1, 1}, {1, -1},  {-1, 1}, {-1, -1}};
    static const int kingSteps[8][2] = {{1, 0},  {-1, 0}, {0, 1},  {0, -1},
                                        {1, 1}, {1, -1},  {-1, 1}, {-1, -1}};

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            const Piece* piece = squares_[r][c];
            if (piece == nullptr || piece->getColor() != color) {  // не наша фигура
                continue;
            }

            switch (piece->getType()) {
                case PieceType::Pawn: {
                    const int dir = (color == Color::White) ? -1 : 1;
                    const int startRow = (color == Color::White) ? 6 : 1;
                    tryAddLegalMove(*this, moves, r, c, r + dir, c, color);
                    if (r == startRow) {  // двойной ход с начальной линии
                        tryAddLegalMove(*this, moves, r, c, r + 2 * dir, c, color);
                    }
                    tryAddLegalMove(*this, moves, r, c, r + dir, c - 1, color);
                    tryAddLegalMove(*this, moves, r, c, r + dir, c + 1, color);
                    break;
                }
                case PieceType::Knight:
                    for (int i = 0; i < 8; ++i) {
                        tryAddLegalMove(*this, moves, r, c, r + knightJumps[i][0],
                                        c + knightJumps[i][1], color);
                    }
                    break;
                case PieceType::Bishop:
                    addRayMoves(*this, moves, r, c, color, bishopDirs, 4);
                    break;
                case PieceType::Rook:
                    addRayMoves(*this, moves, r, c, color, rookDirs, 4);
                    break;
                case PieceType::Queen:
                    addRayMoves(*this, moves, r, c, color, queenDirs, 8);
                    break;
                case PieceType::King:
                    for (int i = 0; i < 8; ++i) {
                        tryAddLegalMove(*this, moves, r, c, r + kingSteps[i][0],
                                        c + kingSteps[i][1], color);
                    }
                    tryAddLegalMove(*this, moves, r, c, r, c + 2, color);  // короткая рокировка
                    tryAddLegalMove(*this, moves, r, c, r, c - 2, color);  // длинная рокировка
                    break;
                default:
                    break;
            }
        }
    }
    return moves;
}

// выполнить ход на доске
MoveUndo Board::makeMove(const Move& move) {
    MoveUndo undo;
    undo.move = move;
    undo.enPassantTargetBefore = enPassantTarget_;
    undo.enPassantValidBefore = enPassantValid_;
    undo.halfMoveClockBefore = halfMoveClock_;
    undo.fullMoveNumberBefore = fullMoveNumber_;
    undo.rookHadMovedBefore = false;
    undo.enPassantCapture = false;

    Piece* piece = squares_[move.from.row][move.from.col];
    if (piece == nullptr) {  // пустая исходная клетка
        return undo;
    }
    undo.movedPieceHadMoved = piece->hasMoved();

    if (piece->getType() == PieceType::King && std::abs(move.to.col - move.from.col) == 2) {
        const int rookFromCol = (move.to.col > move.from.col) ? 7 : 0;
        if (squares_[move.from.row][rookFromCol] == nullptr) {  // нет ладьи для рокировки
            return undo;
        }
    }

    enPassantValid_ = false;
    enPassantTarget_ = Position(-1, -1);

    Piece* captured = squares_[move.to.row][move.to.col];
    undo.capturedHadMoved = captured != nullptr ? captured->hasMoved() : false;
    bool didCapture = false;
    if (captured != nullptr) {  // обычное взятие
        didCapture = true;
        undo.move.capturedType = captured->getType();
        delete captured;
        captured = nullptr;
        squares_[move.to.row][move.to.col] = nullptr;
    }

    // взятие на проходе
    if (piece->getType() == PieceType::Pawn && !didCapture &&
        move.from.col != move.to.col) {
        const int capRow = move.from.row;
        Piece* epVictim = squares_[capRow][move.to.col];
        if (epVictim != nullptr) {
            undo.capturedHadMoved = epVictim->hasMoved();
            undo.move.capturedType = PieceType::Pawn;
            delete epVictim;
            squares_[capRow][move.to.col] = nullptr;
            didCapture = true;
            undo.enPassantCapture = true;
        }
    }
    undo.move.isCapture = didCapture;
    undo.move.pieceType = piece->getType();

    // рокировка
    if (piece->getType() == PieceType::King && std::abs(move.to.col - move.from.col) == 2) {
        const int rookFromCol = (move.to.col > move.from.col) ? 7 : 0;
        const int rookToCol = (move.to.col > move.from.col) ? 5 : 3;
        Piece* rook = squares_[move.from.row][rookFromCol];
        undo.rookHadMovedBefore = rook->hasMoved();
        squares_[move.from.row][rookFromCol] = nullptr;
        squares_[move.from.row][rookToCol] = rook;
        rook->setPosition(move.from.row, rookToCol);
        rook->setHasMoved(true);
    }

    squares_[move.from.row][move.from.col] = nullptr;
    squares_[move.to.row][move.to.col] = piece;
    piece->setPosition(move.to.row, move.to.col);
    piece->setHasMoved(true);

    if (piece->getType() == PieceType::Pawn) {
        if (std::abs(move.to.row - move.from.row) == 2) {  // двойной ход пешки
            enPassantValid_ = true;
            enPassantTarget_ = Position((move.from.row + move.to.row) / 2, move.from.col);
        }
        halfMoveClock_ = 0;
    } else if (didCapture) {
        halfMoveClock_ = 0;
    } else {
        ++halfMoveClock_;
    }

    if (move.isPromotion) {  // замена пешки на фигуру
        delete piece;
        squares_[move.to.row][move.to.col] =
            createPiece(move.promotionTo, move.player, move.to.row, move.to.col);
        squares_[move.to.row][move.to.col]->setHasMoved(true);
        undo.move.isPromotion = true;
        undo.move.promotionTo = move.promotionTo;
    }

    if (move.player == Color::Black) {  // полный ход после чёрных
        ++fullMoveNumber_;
    }

    activeColor_ = oppositeColor(move.player);
    return undo;
}

// отменить ранее выполненный ход
void Board::unmakeMove(const MoveUndo& undo) {
    const Move& move = undo.move;
    activeColor_ = move.player;

    if (move.player == Color::Black) {
        fullMoveNumber_ = undo.fullMoveNumberBefore;
    }

    halfMoveClock_ = undo.halfMoveClockBefore;
    enPassantTarget_ = undo.enPassantTargetBefore;
    enPassantValid_ = undo.enPassantValidBefore;

    Piece* piece = squares_[move.to.row][move.to.col];

    if (move.isPromotion) {  // вернуть пешку вместо фигуры
        delete piece;
        piece = createPiece(PieceType::Pawn, move.player, move.from.row, move.from.col);
    }

    squares_[move.to.row][move.to.col] = nullptr;
    squares_[move.from.row][move.from.col] = piece;
    piece->setPosition(move.from.row, move.from.col);
    piece->setHasMoved(undo.movedPieceHadMoved);

    // отмена рокировки
    if (move.pieceType == PieceType::King && std::abs(move.to.col - move.from.col) == 2) {
        const int rookFromCol = (move.to.col > move.from.col) ? 7 : 0;
        const int rookToCol = (move.to.col > move.from.col) ? 5 : 3;
        Piece* rook = squares_[move.from.row][rookToCol];
        squares_[move.from.row][rookToCol] = nullptr;
        squares_[move.from.row][rookFromCol] = rook;
        rook->setPosition(move.from.row, rookFromCol);
        rook->setHasMoved(undo.rookHadMovedBefore);
    }

    // восстановление взятой фигуры
    if (move.isCapture) {
        if (undo.enPassantCapture) {  // вернуть пешку, взятую на проходе
            Piece* epPawn = createPiece(PieceType::Pawn, oppositeColor(move.player),
                                        move.from.row, move.to.col);
            epPawn->setHasMoved(undo.capturedHadMoved);
            squares_[move.from.row][move.to.col] = epPawn;
        } else {
            Piece* restored =
                createPiece(move.capturedType, oppositeColor(move.player),
                            move.to.row, move.to.col);
            restored->setHasMoved(undo.capturedHadMoved);
            squares_[move.to.row][move.to.col] = restored;
        }
    }
}

// определить статус партии
GameStatus Board::getGameStatus() {
    const Color side = activeColor_;
    const std::vector<Move> moves = generateLegalMoves(side);
    const bool inCheck = isKingInCheck(side);

    if (!moves.empty()) {  // есть легальные ходы
        return inCheck ? GameStatus::Check : GameStatus::InProgress;
    }
    return inCheck ? GameStatus::Checkmate : GameStatus::Stalemate;
}

// счётчик полуходов без взятий и пешечных ходов
int Board::getHalfMoveClock() const { return halfMoveClock_; }

// ничья по правилу 50 ходов
bool Board::isFiftyMoveRuleDraw() const { return halfMoveClock_ >= 100; }

// построить строковый ключ позиции
std::string Board::getPositionKey() const {
    std::ostringstream key;
    key << (activeColor_ == Color::White ? 'W' : 'B') << '|';
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (squares_[r][c] == nullptr) {
                key << '.';
            } else {
                key << squares_[r][c]->getSymbol();
            }
        }
    }
    key << '|';
    if (enPassantValid_) {
        key << "ep" << enPassantTarget_.row << enPassantTarget_.col;
    } else {
        key << "ep-";
    }
    key << '|';
    const Piece* wk = getPiece(7, 4);
    const Piece* bk = getPiece(0, 4);

    const Piece* wkr = getPiece(7, 7);
    const Piece* wqr = getPiece(7, 0);
    const Piece* bkr = getPiece(0, 7);
    const Piece* bqr = getPiece(0, 0);

    // белая короткая рокировка
    if (wk != nullptr && !wk->hasMoved() &&
        wkr != nullptr && wkr->getType() == PieceType::Rook && !wkr->hasMoved()) {
        key << 'K';
    } else {
        key << '-';
    }

    // белая длинная рокировка
    if (wk != nullptr && !wk->hasMoved() &&
        wqr != nullptr && wqr->getType() == PieceType::Rook && !wqr->hasMoved()) {
        key << 'Q';
    } else {
        key << '-';
    }

    // чёрная короткая рокировка
    if (bk != nullptr && !bk->hasMoved() &&
        bkr != nullptr && bkr->getType() == PieceType::Rook && !bkr->hasMoved()) {
        key << 'k';
    } else {
        key << '-';
    }

    // чёрная длинная рокировка
    if (bk != nullptr && !bk->hasMoved() &&
        bqr != nullptr && bqr->getType() == PieceType::Rook && !bqr->hasMoved()) {
        key << 'q';
    } else {
        key << '-';
    }

    return key.str();
}

// текстовое ASCII-представление доски
std::string Board::toAscii() const {
    std::ostringstream out;
    out << "  +---+---+---+---+---+---+---+---+\n";
    for (int r = 0; r < 8; ++r) {
        out << (8 - r) << " |";
        for (int c = 0; c < 8; ++c) {
            char ch = '.';
            if (squares_[r][c] != nullptr) {
                ch = squares_[r][c]->getSymbol();
            }
            out << ' ' << ch << " |";
        }
        out << "\n  +---+---+---+---+---+---+---+---+\n";
    }
    out << "    a   b   c   d   e   f   g   h\n";
    return out.str();
}

// проверка доски для файла
bool Board::isPositionValid() const {
    int whiteKings = 0;
    int blackKings = 0;
    int whitePawns = 0;
    int blackPawns = 0;
    int whiteKingRow = -1;
    int whiteKingCol = -1;
    int blackKingRow = -1;
    int blackKingCol = -1;

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            const Piece* piece = squares_[r][c];
            if (piece == nullptr) {
                continue;
            }

            if (piece->getType() == PieceType::Pawn && (r == 0 || r == 7)) {
                return false;
            }

            if (piece->getColor() == Color::White) {
                if (piece->getType() == PieceType::King) {
                    ++whiteKings;
                    whiteKingRow = r;
                    whiteKingCol = c;
                } else if (piece->getType() == PieceType::Pawn) {
                    ++whitePawns;
                }
            } else {
                if (piece->getType() == PieceType::King) {
                    ++blackKings;
                    blackKingRow = r;
                    blackKingCol = c;
                } else if (piece->getType() == PieceType::Pawn) {
                    ++blackPawns;
                }
            }
        }
    }

    if (whiteKings != 1 || blackKings != 1) {
        return false;
    }
    if (whitePawns > 8 || blackPawns > 8) {
        return false;
    }

    const int dr = std::abs(whiteKingRow - blackKingRow);
    const int dc = std::abs(whiteKingCol - blackKingCol);
    if (dr <= 1 && dc <= 1) {
        return false; // короли не могут стоять рядом
    }

    if (isKingInCheck(oppositeColor(activeColor_))) {
        return false; // у стороны, не имеющей хода, король не под шахом
    }

    return true;
}