#include "Core/ChessGame.h"

#include "Pieces/Piece.h"

// деструктор интерфейса колбэков UI
IGameUiCallbacks::~IGameUiCallbacks() = default;

// создать партию: белые ходят первыми
ChessGame::ChessGame(Player* whitePlayer, Player* blackPlayer)
    : whitePlayer_(whitePlayer),
      blackPlayer_(blackPlayer),
      currentPlayer_(whitePlayer),
      uiCallbacks_(nullptr),
      plyCount_(0),
      drawDeclared_(false),
      drawStatus_(GameStatus::InProgress) {
    history_.recordPosition(board_.getPositionKey());
}

// деструктор контроллера партии
ChessGame::~ChessGame() = default;

// установить указатель на колбэки UI
void ChessGame::setUiCallbacks(IGameUiCallbacks* callbacks) { uiCallbacks_ = callbacks; }

// загрузить позицию из файла (формат как positions/sample.txt)
bool ChessGame::loadPosition(const std::string& filePath) {
    Board loaded(filePath);
    if (!loaded.isPositionLoaded()) {
        return false;
    }
    board_ = loaded;
    history_ = GameHistory();
    history_.recordPosition(board_.getPositionKey());
    plyCount_ = 0;
    drawDeclared_ = false;
    drawStatus_ = GameStatus::InProgress;
    currentPlayer_ = whitePlayer_;
    return true;
}

// вернуть доску
Board& ChessGame::getBoard() { return board_; }
// вернуть историю
const GameHistory& ChessGame::getHistory() const { return history_; }
// вернуть игрока на ходу
Player* ChessGame::getCurrentPlayer() const { return currentPlayer_; }
// число полуходов
int ChessGame::getPlyCount() const { return plyCount_; }

// вернуть статус: объявленная ничья или с доски
GameStatus ChessGame::getStatus() {
    // ничья уже зафиксирована контроллером
    if (drawDeclared_) {
        return drawStatus_;
    }
    return board_.getGameStatus();
}

// конечный ли статус (мат, пат, ничья)
bool ChessGame::isTerminalStatus(GameStatus status) const {
    return status == GameStatus::Checkmate || status == GameStatus::Stalemate ||
           status == GameStatus::DrawFiftyMove ||
           status == GameStatus::DrawThreefoldRepetition;
}

// партия завершена объявленной ничьей или статусом доски
bool ChessGame::isGameOver() {
    if (drawDeclared_) {
        return true;
    }
    return isTerminalStatus(board_.getGameStatus());
}

// сменить текущего игрока на противника
void ChessGame::switchTurn() {
    currentPlayer_ = (currentPlayer_ == whitePlayer_) ? blackPlayer_ : whitePlayer_;
}

// сформировать короткое сообщение для UI по статусу
std::string ChessGame::buildStatusMessage(GameStatus status) const {
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
            return "OK";
    }
}

// дополнить Move типом фигуры, взятием и взятием на проходе
void ChessGame::finalizeMoveMetadata(Move& move) const {
    const Piece* piece = board_.getPiece(move.from.row, move.from.col);
    if (piece != nullptr) {
        move.pieceType = piece->getType();
    }
    const Piece* captured = board_.getPiece(move.to.row, move.to.col);
    move.isCapture = captured != nullptr && captured->getColor() != move.player;
    move.capturedType = move.isCapture ? captured->getType() : PieceType::None;

    const Position ep = board_.getEnPassantTarget();
    // взятие на проходе: пешка, смена файла, цель совпадает с en passant
    if (piece != nullptr && piece->getType() == PieceType::Pawn && !move.isCapture &&
        move.from.col != move.to.col && ep.row == move.to.row && ep.col == move.to.col) {
        move.isCapture = true;
        move.capturedType = PieceType::Pawn;
    }
}

// после хода: правило 50 ходов, троекратное повторение позиции
GameStatus ChessGame::checkDrawConditions() {
    if (board_.isFiftyMoveRuleDraw()) {
        drawDeclared_ = true;
        drawStatus_ = GameStatus::DrawFiftyMove;
        return drawStatus_;
    }

    const std::string key = board_.getPositionKey();
    history_.recordPosition(key);
    // та же позиция встретилась третий раз
    if (history_.countPosition(key) >= 3) {
        drawDeclared_ = true;
        drawStatus_ = GameStatus::DrawThreefoldRepetition;
        return drawStatus_;
    }
    return board_.getGameStatus();
}

// один полуход: ввод, проверка, применение, ничья или смена стороны
TurnResult ChessGame::playTurn() {
    TurnResult result;
    result.success = false;
    result.gameOver = isGameOver();
    result.status = getStatus();

    // нельзя ходить после окончания партии
    if (result.gameOver) {
        result.message = "Game already finished";
        return result;
    }

    while (true) {
        Move move;
        if (!currentPlayer_->requestMove(board_, move)) {
            result.message = "Move input cancelled or exhausted";
            result.gameOver = true;
            return result;
        }

        move.player = currentPlayer_->getColor();
        finalizeMoveMetadata(move);

        if (!board_.isLegalMove(move)) {
            const std::string warning = "Illegal move. Please try again.";
            if (uiCallbacks_ != nullptr) {
                uiCallbacks_->onWarning(warning);
            }
            // повторить ввод при незаконном ходе, если игрок это разрешает
            if (currentPlayer_->allowsRetryOnIllegalMove()) {
                continue;
            }
            result.message = warning;
            return result;
        }

        board_.makeMove(move);
        history_.addMove(move, (plyCount_ / 2) + 1);
        ++plyCount_;

        result.status = checkDrawConditions();
        // ничья или мат/пат без смены хода
        if (drawDeclared_ || isTerminalStatus(result.status)) {
            result.gameOver = true;
        } else {
            switchTurn();
            result.status = board_.getGameStatus();
            // шах без мата — партия продолжается; мат/пат — конец
            if (isTerminalStatus(result.status)) {
                result.gameOver = true;
            }
        }

        result.success = true;
        result.move = move;
        result.message = buildStatusMessage(result.status);
        return result;
    }
}
