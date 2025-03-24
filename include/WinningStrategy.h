#ifndef WINNINGSTRATEGY_H
#define WINNINGSTRATEGY_H

#include "Board.h"

class WinningStrategy
{
public:
    // Pure virtual function to determine if a win condition is met for 'symbol'
    virtual bool isWinningMove(Board &board, char symbol) const = 0;
    virtual ~WinningStrategy() = default;
};

class RowWinStrategy : public WinningStrategy
{
public:
    bool isWinningMove(Board &board, char symbol) const override;
};

class DiagonalWinStrategy : public WinningStrategy
{
public:
    bool isWinningMove(Board &board, char symbol) const override;
};

class CornersWinStrategy : public WinningStrategy
{
public:
    bool isWinningMove(Board &board, char symbol) const override;
};

#endif // WINNINGSTRATEGY_H