# Chess — краткая документация

Консольная и GUI (SFML) шахматы с ООП: полиморфные фигуры, игроки, стратегия ИИ, разделение логики и UI.

## Структура каталогов

| Папка | Назначение |
|-------|------------|
| `Core/` | Типы, доска, история, контроллер партии |
| `Pieces/` | Иерархия фигур и фабрика |
| `Players/` | Игроки и ввод хода |
| `AI/` | Стратегии ИИ (Strategy) |
| `UI/` | `main.cpp`, консоль, SFML |
| `positions/` | Текстовые позиции (`sample.txt`) |
| `docs/` | Вся документация: `PROJECT.md`, `Модельная диаграмма.svg`, `Функциональная схема.drawio.svg` |

Сборка: `build_console.bat` → `chess.exe console`; `build_sfml.bat` → с GUI (`chess.exe gui`). Запуск из **корня проекта** (пути к `positions/`).

---

## Режимы (`UI/main.cpp`)

| Режим | Описание |
|-------|----------|
| 1 | Human (белые) vs AI (чёрные), стартовая позиция |
| 2 | Human vs Human |
| 3 | Автотесты правил → консоль + `out.txt` |
| 4 | AI vs AI, доска из `positions/sample.txt`, лог ходов |

---

## Core

### `ChessTypes` (`Core/ChessTypes.h`, `.cpp`)

**Типы:** `Color`, `PieceType`, `Position`, `Move`, `MoveUndo`.

| Сущность | Поля / смысл |
|----------|----------------|
| `Position` | `row`, `col` (0 = 8-я горизонталь); `isOnBoard()` |
| `Move` | `from`, `to`, `player`, типы фигур, флаги взятия и превращения |
| `MoveUndo` | снимок для `Board::unmakeMove` |

**Функции:** `oppositeColor`, `colorToString`, `pieceTypeToString`, `pieceMaterialValue`, `isPromotionPiece`, `promotionPieceToChar`.

---

### `GameStatus` (`Core/Board.h`)

`InProgress`, `Check`, `Checkmate`, `Stalemate`, `DrawFiftyMove`, `DrawThreefoldRepetition`.

---

### `Board`

Доска 8×8, правила, make/unmake для поиска ИИ.

| Метод | Назначение |
|-------|------------|
| `Board()` | Начальная позиция |
| `Board(filePath)` | Загрузка из файла; `isPositionLoaded()` |
| `resetToStartingPosition()` / `clear()` | Стандарт или пустая доска |
| `getPiece` / `setPiece` | Клетка |
| `getActiveColor` / `setActiveColor` | Очередь хода |
| `getEnPassantTarget` | Цель взятия на проходе |
| `isSquareAttacked`, `isKingInCheck` | Атаки и шах |
| `isLegalMove`, `generateLegalMoves` | Легальные ходы (с учётом шаха) |
| `makeMove` / `unmakeMove` | Ход и откат |
| `getGameStatus` | Мат / пат / шах / игра |
| `toAscii`, `getPositionKey` | Вывод и ключ для повторов |
| `getHalfMoveClock`, `isFiftyMoveRuleDraw` | Правило 50 ходов |
| `isPathClear`, `isCastlingPathSafe` | Скольжение и рокировка |

**Формат файла позиции** (`positions/sample.txt`):

```
White: 3
QA4
...
Black: 6
pA5
...
```

Строка фигуры: буква типа + клетка (`Q`, `K`, `N`, `R`, `B`, `p`… + `A1`…`H8`).

---

### `GameHistory`

| Метод | Назначение |
|-------|------------|
| `addMove(move, fullMoveNumber)` | Запись хода в список |
| `recordPosition(key)` | Ключ позиции для ничьей по повтору |
| `countPosition(key)` | Сколько раз встречалась позиция |
| `size`, `getEntry` | Доступ к записям |
| `formatAll()` | Текст истории для консоли |

`HistoryEntry`: номер хода, цвет, `Move`.

---

### `ChessGame`

Контроллер: не читает stdin сам (кроме опциональных колбэков).

| Метод | Назначение |
|-------|------------|
| `ChessGame(white, black)` | Старт с начальной позиции; `currentPlayer_` → белые |
| `setUiCallbacks` | Предупреждения в UI (`IGameUiCallbacks`) |
| `getBoard`, `getHistory`, `getCurrentPlayer` | Доступ к состоянию |
| `getStatus`, `isGameOver`, `getPlyCount` | Статус и счётчик полуходов |
| `playTurn()` | Один ход: `requestMove` → проверка → `makeMove` → ничья/смена стороны → `TurnResult` |
| `loadPosition(filePath)` | Подмена доски, сброс истории (режим 4) |

**`IGameUiCallbacks`:** `onWarning(message)`.

**`TurnResult`:** `success`, `gameOver`, `move`, `status`, `message`.

---

## Pieces

### `Piece` (абстрактный)

| Метод | Назначение |
|-------|------------|
| `clone()` | Полиморфная копия |
| `getType()`, `getSymbol()` | Тип и символ ASCII |
| `isValidMove(board, toRow, toCol)` | Геометрия хода (без шаха — фильтрует `Board`) |
| `getColor`, `getRow`, `getCol`, `hasMoved` | Состояние |
| `setPosition`, `setHasMoved` | После хода / рокировки |

### Наследники

`Pawn`, `Rook`, `Knight`, `Bishop`, `Queen`, `King` — в каждом свой `.h`/`.cpp; переопределяют `clone`, `getType`, `getSymbol`, `isValidMove`. У короля — рокировка; у пешки — двойной ход, взятие на проходе (в связке с `Board`).

### `createPiece` (`PieceFactory`)

Создаёт `Piece*` по `PieceType`, цвету и координатам.

---

## Players

### `Player` (абстрактный)

| Метод | Назначение |
|-------|------------|
| `requestMove(board, outMove)` | Получить ход |
| `getName()` | Строка для UI |
| `allowsRetryOnIllegalMove()` | Повтор ввода (Human — да) |

### `HumanPlayer`

| Метод | Назначение |
|-------|------------|
| `requestMove` | `IPlayerInput::readMove`, при превращении — `readPromotionChoice` |
| `allowsRetryOnIllegalMove` | `true` |

### `ScriptedPlayer`

| Метод | Назначение |
|-------|------------|
| `requestMove` | Следующий ход из заданного массива (для тестов) |

### `AIPlayer`

| Метод | Назначение |
|-------|------------|
| `requestMove` | `AIStrategy::chooseMove` |
| `setStrategy` | Замена стратегии |
| Копирование | Глубокая копия стратегии через `clone()` |

### `IPlayerInput` / `ConsolePlayerInput`

| Метод | Назначение |
|-------|------------|
| `readMove` | Ввод «e2 e4» (консоль) или клики (SFML через `SfmlPlayerInput`) |
| `readPromotionChoice` | Q / R / B / N |

`SfmlPlayerInput` объявлен в `UI/SfmlFrontend.h` — реализация ввода для GUI.

---

## AI

### `AIStrategy` (интерфейс, Strategy)

| Метод | Назначение |
|-------|------------|
| `chooseMove(board, aiColor, outMove)` | Выбор хода |
| `clone()` | Копия для `AIPlayer` |

### `MinimaxAlphaBetaStrategy`

| Метод | Назначение |
|-------|------------|
| `chooseMove` | Поиск на копии доски по всем легальным ходам |
| `evaluateBoard` | Материальная оценка |
| `minimax` | Рекурсия с alpha-beta; `makeMove` / `unmakeMove` на доске |

Параметр конструктора: `searchDepth` (глубина в полуходах).

---

## UI

### `ConsolePresenter` / `ConsoleUiCallbacks`

| Метод | Назначение |
|-------|------------|
| `printBoard` | ASCII-доска |
| `printTurnHeader` | Чей ход |
| `printTurnResult` | Координаты хода и статус |
| `printHistory` | История из `GameHistory` |
| `printLine`, `printHelp` | Сообщения и справка |
| `ConsoleUiCallbacks::onWarning` | `[!] сообщение` |

### `SfmlFrontend` (сборка с `CHESS_WITH_SFML`)

| Метод | Назначение |
|-------|------------|
| `draw`, `drawThinking` | Отрисовка доски и статуса |
| `waitForMove`, `waitForPromotion` | Ввод мышью |
| `setBanner`, `setWarning`, `clearWarning` | Тексты на экране |
| `showEndScreen`, `waitUntilClosed` | Конец партии |
| `isOpen`, `close`, `pumpFrame` | Жизненный цикл окна |

### `SfmlUiCallbacks`

`onWarning` → показ в GUI.

### `main.cpp`

`runConsole()` — режимы 1–4; `runRuleChecks()` — режим 3; `runSfml()` — GUI (human vs AI). Точка входа: аргумент `console` / `gui`.

---

## Поток одного хода (кратко)

1. `ChessGame::playTurn` → `currentPlayer_->requestMove`
2. Проверка `board_.isLegalMove`
3. `board_.makeMove`, `history_.addMove`, проверка ничьи
4. `switchTurn()` — `currentPlayer_` указывает на другого агрегированного `Player`
5. UI печатает результат (вне `ChessGame`)

---

## Зависимости между слоями

```
UI (main, Presenter, SFML)
    → ChessGame, Players, AI
        → Board, GameHistory, Pieces
            → ChessTypes
```

`Board` не знает об UI; `ChessGame` не выводит в консоль (только колбэки). ИИ работает только с `Board` и `AIStrategy`.
