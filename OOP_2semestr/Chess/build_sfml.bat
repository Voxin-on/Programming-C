@echo off
setlocal
cd /d "%~dp0"

set SFML=SFML-3.1.0
set FLAGS=-std=c++17 -O2 -I. -I%SFML%/include -DCHESS_WITH_SFML
set LIB=-L%SFML%/lib

set CORE=Core\ChessTypes.cpp Core\Board.cpp Core\GameHistory.cpp Core\ChessGame.cpp
set PIECES=Pieces\Piece.cpp Pieces\Pawn.cpp Pieces\Rook.cpp Pieces\Knight.cpp Pieces\Bishop.cpp Pieces\Queen.cpp Pieces\King.cpp Pieces\PieceFactory.cpp
set PLAYERS=Players\Player.cpp Players\HumanPlayer.cpp Players\ScriptedPlayer.cpp Players\AIPlayer.cpp Players\PlayerInput.cpp
set AI=AI\AIStrategy.cpp AI\MinimaxAlphaBetaStrategy.cpp
set UI=UI\ConsolePresenter.cpp UI\SfmlFrontend.cpp UI\main.cpp

g++ %FLAGS% %CORE% %PIECES% %PLAYERS% %AI% %UI% %LIB% -o chess.exe ^
  -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lwinmm -lgdi32

if errorlevel 1 (
  echo Build failed. Check SFML-3.1.0/lib and bin.
  exit /b 1
)

copy /Y "%SFML%\bin\sfml-graphics-3.dll" . >nul 2>&1
copy /Y "%SFML%\bin\sfml-window-3.dll" . >nul 2>&1
copy /Y "%SFML%\bin\sfml-system-3.dll" . >nul 2>&1

echo OK: chess.exe  (chess.exe console   chess.exe gui)
endlocal
