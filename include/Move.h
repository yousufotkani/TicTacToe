#ifndef MOVE_H
#define MOVE_H

#include "Player.h"

class Player;

struct Move
{
    int row;
    int col;
    Player *previousPlayer;
    char previousSymbol;

    // Constructor
    Move(int row, int col, char previousSymbol, Player *player)
    {
        this->row = row;
        this->col = col;
        this->previousPlayer = player;
        this->previousSymbol = previousSymbol;
    }
};

#endif // MOVE_H
