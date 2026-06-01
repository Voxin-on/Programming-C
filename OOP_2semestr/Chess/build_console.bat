@echo off
setlocal
cd /d "%~dp0"

set FLAGS=-std=c++17 -O2 -I.

set CORE=Core\ChessTypes.cpp Core\Board.cpp Core\GameHistory.cpp Core\ChessGame.cpp
set PIECES=Pieces\Piece.cpp Pieces\Pawn.cpp Pieces\Rook.cpp Pieces\Knight.cpp Pieces\Bishop.cpp Pieces\Queen.cpp Pieces\King.cpp Pieces\PieceFactory.cpp
set PLAYERS=Players\Player.cpp Players\HumanPlayer.cpp Players\ScriptedPlayer.cpp Players\AIPlayer.cpp Players\PlayerInput.cpp
set AI=AI\AIStrategy.cpp AI\MinimaxAlphaBetaStrategy.cpp
set UI=UI\ConsolePresenter.cpp UI\main.cpp

g++ %FLAGS% %CORE% %PIECES% %PLAYERS% %AI% %UI% -o chess.exe
if errorlevel 1 exit /b 1

echo OK: chess.exe  (run: chess.exe console)
endlocal
