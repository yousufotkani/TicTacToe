# TicTacToe
This is a Simple TicTactoe game i wrote to understand some low level concepts of Object Oriented Design and practices.

The codebase aims to follow the best practices of SOLID, DRY, YAGNI Principles. Mainly Liskov's Subs Principle which has fascinated me very much!

A key design Patters used in this code is
1. Strategy Design Pattern (to select different strategies to decide the winner). If the client wants to add a new winning strategy, they can easily extend the behavior.

Features:
1. Undo Functionality.
2. If there is only one player, user can play with a bot.

TODO:
1. Extend Bot Difficulty.
2. Add Column Winning Strategy.

Procedure to run:
Run Makefile via "make" command and run the ./tictactoe object file.

Follow Class Diagram to understand the codebase:

                +-----------------------+
                |       Game            |
                +-----------------------+
                | - players: vector<Player*>    |
                | - board: Board        |
                | - moveHistory: stack<Move> (for undo) |
                | - winStrategies: vector<WinningStrategy*> |
                +-----------------------+
                | + playGame()          |
                | + undoMove()          |
                | + checkWin(symbol): bool |
                | + chooseRandomStart() |
                +-----------------------+
                           |
                           | uses
                           v
                +-----------------------+
                |       Board           |
                +-----------------------+
                | - size: int           |
                | - grid: vector<vector<Grid>>  |
                +-----------------------+
                | + displayGrid()       |
                | + updateGrid(row, col, symbol)|
                | + getCellSymbol(row, col): char |
                | + isFull(): bool      |
                | + checkWin(symbol): bool |
                +-----------------------+
                           |
                           | consists of
                           v
                +-----------------------+
                |       Grid            |
                +-----------------------+
                | - row: int            |
                | - col: int            |
                | - state: enum { AVAILABLE, NOT_AVAILABLE, BLOCKED } |
                | - occupant: Player*   |
                +-----------------------+
                           
                           
                +-----------------------+
                |        Move           |
                +-----------------------+
                | - row: int            |
                | - col: int            |
                | - previousSymbol: char|
                +-----------------------+

                           
                +-----------------------+
                |    WinningStrategy    |  <-- Abstract Strategy (Strategy Pattern)
                +-----------------------+
                | + isWinningMove(const Board&, char): bool = 0 |
                +-----------------------+
                           ^
                           |  implements
          +----------------+----------------+---------------------+
          |                                 |                     |
          v                                 v                     v
+--------------------+          +---------------------+   +---------------------+
|  RowWinStrategy    |          |  DiagonalWinStrategy|   |  CornersWinStrategy |     //ColumnStrategy can be extended.
+--------------------+          +---------------------+   +---------------------+
| + isWinningMove(...)|         | + isWinningMove(...)|   | + isWinningMove(...)|
+--------------------+          +---------------------+   +---------------------+

                           
                +-----------------------+
                |       Player          |  <-- Abstract Class
                +-----------------------+
                | - playerName: string  |
                | - symbol: char        |
                | - moves: vector<Move> (optional) |
                +-----------------------+
                | + getMove(Board&): pair<int,int> = 0 |
                | + getName(): string   |
                | + getSymbol(): char   |
                +-----------------------+
                           ^
                           |  inherits
           +---------------+---------------+
           |                               |
           v                               v
+----------------------+          +----------------------+
|    HumanPlayer       |          |      BotPlayer       |
+----------------------+          +----------------------+
| + getMove(Board&):   |          | - difficulty: enum {EASY, MEDIUM, HARD} |
|   pair<int,int>      |          | + getMove(Board&): pair<int,int>        |
+----------------------+          +----------------------+




