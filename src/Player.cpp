#include "Player.h"

// For BOT
#include "Board.h" // To use Board's methods (e.g., getCellSymbol, getSize)
#include <cstdlib>
#include <ctime>
#include <iostream>

class Board;

using namespace std;

Player::Player(const std::string &name, char sym)
{
    this->playerName = name;
    this->symbol = sym;
}

Player::~Player()
{
    // Cleanup if needed
}

std::string Player::getName() const
{
    return playerName;
}

char Player::getSymbol() const
{
    return symbol;
}

// Human Player
HumanPlayer::HumanPlayer(const std::string &name, char sym)
    : Player(name, sym)
{
}

HumanPlayer::~HumanPlayer() {}

std::pair<int, int> HumanPlayer::getMove(Board &board)
{
    int row, col;
    cout << "Player " << playerName << " (" << symbol << ") - Enter your move (row col)" << endl;
    cout << "If you want to undo previous move, enter (-1 -1) : ";
    cin >> row >> col;
    return std::make_pair(row, col);
}

// BOT Player
BotPlayer::BotPlayer(const std::string &name, char sym, Difficulty diff)
    : Player(name, sym), difficulty(diff)
{
    // seed the random generator if not seeded elsewhere.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

BotPlayer::~BotPlayer() {}

std::pair<int, int> BotPlayer::getMove(Board &board)
{
    // Example implementation: choose a random empty cell.
    // Assumes Board provides getSize() method. If not, adjust accordingly.
    int boardSize = board.getSize(); // Ensure Board has this method.
    int row, col;
    do
    {
        row = std::rand() % boardSize;
        col = std::rand() % boardSize;
    } while (board.getCellSymbol(row, col) != '-'); // Assume '-' indicates an empty cell.

    cout << "Bot " << playerName << " (" << symbol << ") chooses move ("
         << row << ", " << col << ")\n";
    return make_pair(row, col);
}
