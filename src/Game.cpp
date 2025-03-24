#include "Game.h"

Game::Game(int boardSize)
{
    // seed random generator api
    srand(static_cast<unsigned int>(time(nullptr)));

    board = new Board(boardSize);
    startingPlayerIndex = 0;
    // add winning strategies...
    winStrategies.push_back(new RowWinStrategy());
    winStrategies.push_back(new DiagonalWinStrategy());
    winStrategies.push_back(new CornersWinStrategy());
}

Game::~Game()
{
    delete board;
    for (auto p : players)
    {
        delete p;
    }
    for (auto strat : winStrategies)
    {
        delete strat;
    }
}

const std::vector<Player *> &Game::getPlayers() const
{
    return players;
}

// Adds a player to the game
void Game::addPlayer(Player *player)
{
    players.push_back(player);
}

// Choose a random starting player from the players vector
int Game::chooseRandomStart()
{
    if (players.empty())
    {
        return -1; // or handle error appropriately
    }
    startingPlayerIndex = rand() % players.size();
    return startingPlayerIndex;
}

// Check win conditions by iterating through all winning strategies
bool Game::checkWin(char symbol)
{
    for (auto strat : winStrategies)
    {
        if (strat->isWinningMove(*board, symbol))
            return true;
    }
    return false;
}

// Undo the last move using the move history
void Game::undoMove()
{
    if (moveHistory.empty())
    {
        std::cout << "No moves to undo!" << std::endl;
        return;
    }
    Move lastMove = moveHistory.top();
    moveHistory.pop();
    board->updateGrid(lastMove.row, lastMove.col, lastMove.previousSymbol, lastMove.previousPlayer);
    std::cout << "Undo move at (" << lastMove.row << ", " << lastMove.col << ")" << std::endl;
}

// Main game loop
void Game::playGame()
{
    std::cout << "Game started with " << players.size() << " players." << std::endl;
    if (chooseRandomStart() != -1)
    {
        std::cout << "Random starting player Name: " << players[startingPlayerIndex]->getName()  << std::endl;
    }
    // Continue game until a win or draw condition is met.
    while (true)
    {
        board->displayGrid();

        // Current player's turn
        Player *currentPlayer = players[startingPlayerIndex];
        std::pair<int, int> move = currentPlayer->getMove(*board);
        int row = move.first, col = move.second;
        
        //if row and col are both -1, we can use this info to undo.
        if (row == -1 && col == -1)
        {
            undoMove();
            continue;
        }

        // Save the previous symbol for undo purposes
        char prevSymbol = board->getCellSymbol(row, col);
        Player *prevPlayer = board->getCellPlayer(row, col);
        // Attempt to update the grid; assuming updateGrid returns a bool (true if move valid)
        if (!board->updateGrid(row, col, currentPlayer->getSymbol(), currentPlayer))
        {
            std::cout << "Invalid move. Try again." << std::endl;
            continue;
        }
        // Record the move in the history
        moveHistory.push(Move{row, col, prevSymbol, prevPlayer});

        // Check win condition for the current player's symbol
        if (checkWin(currentPlayer->getSymbol()))
        {
            board->displayGrid();
            std::cout << "Player " << currentPlayer->getName() << " wins!" << std::endl;
            break;
        }

        // Check for a draw; assuming board->isFull() returns true when board is full
        if (board->isFull())
        {
            board->displayGrid();
            std::cout << "The game is a draw." << std::endl;
            break;
        }

        // Rotate to the next player in a round-robin fashion
        startingPlayerIndex = (startingPlayerIndex + 1) % players.size();
    }
}