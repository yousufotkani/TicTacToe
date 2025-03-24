#ifndef GAME_H
#define GAME_H

#include <vector>
#include <stack>
#include <string>
#include <utility>

#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

#include "Board.h"
#include "Player.h"
#include "Move.h"
#include "WinningStrategy.h"

using namespace std;

 // Fwd Declaration
 class Board;
 class Player;
 struct Move;
 class WinningStrategy;

class Game
{
private:
    Board *board;                            // Pointer to the game board
    vector<Player *> players;                // List of players (n players)
    stack<Move> moveHistory;                 // Compile time alloc. sHistory of moves for undo functionality
    vector<WinningStrategy *> winStrategies; // Winning strategy objects
    int startingPlayerIndex;                 // Index of the player whose turn is next

public:
    // Constructor
    Game(int boardSize);
    // Destructor
    ~Game();

    const std::vector<Player *> &getPlayers() const;

    // Adds a player to the game
    void addPlayer(Player *player);

    // Selects a random starting player from players vector
    int chooseRandomStart();

    // Checks if the provided symbol meets any win strategy
    bool checkWin(char symbol);

    // Undoes the last move from the move history
    void undoMove();

    // Main game loop
    void playGame();
};

#endif // GAME_H