#ifndef PLAYER_H
#define PLAYER_H

// Abstract Class

#include <string>
#include <utility>
#include <vector>
#include "Move.h"  // Assuming Move.h defines the Move struct.
#include "Board.h" // Forward declaration of Board is enough if needed

class Board;

// Base class for all players (abstract)
class Player
{
protected:
    std::string playerName;
    char symbol;

public:
    // Constructor
    Player(const std::string &name, char sym);

    // Virtual destructor for proper cleanup
    virtual ~Player();

    // Pure virtual function: each derived class must implement how to get a move.
    virtual std::pair<int, int> getMove(Board &board) = 0;

    // Accessors
    std::string getName() const;
    char getSymbol() const;
};

// Derived class for a human player.
class HumanPlayer : public Player
{
public:
    HumanPlayer(const std::string &name, char sym);
    virtual ~HumanPlayer();

    // Implementation of getMove: gets input from the console.
    virtual std::pair<int, int> getMove(Board &board) override;
};

// Derived class for a bot player.

// Enum for bot difficulty levels
enum Difficulty
{
    EASY,
    MEDIUM,
    HARD
};

class BotPlayer : public Player
{
private:
    Difficulty difficulty;

public:
    BotPlayer(const std::string &name, char sym, Difficulty diff);
    virtual ~BotPlayer();

    // Implementation of getMove: bot chooses a move based on its difficulty.
    virtual std::pair<int, int> getMove(Board &board) override;
};

#endif // PLAYER_H
