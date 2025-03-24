#include "WinningStrategy.h"

bool RowWinStrategy::isWinningMove(Board &board, char symbol) const
{
    int size = board.getSize();
    for (int i = 0; i < size; ++i)
    {
        bool rowWin = true;
        for (int j = 0; j < size; ++j)
        {
            if (board.getCellSymbol(i, j) != symbol)
            {
                rowWin = false;
                break;
            }
        }
        if (rowWin)
            return true;
    }
    return false;
}

bool DiagonalWinStrategy::isWinningMove(Board &board, char symbol) const
{
    int size = board.getSize();

    // Check main diagonal
    bool win = true;
    for (int i = 0; i < size; ++i)
    {
        if (board.getCellSymbol(i, i) != symbol)
        {
            win = false;
            break;
        }
    }
    if (win)
        return true;

    // Check anti-diagonal
    win = true;
    for (int i = 0; i < size; ++i)
    {
        if (board.getCellSymbol(i, size - 1 - i) != symbol)
        {
            win = false;
            break;
        }
    }
    return win;
}

bool CornersWinStrategy::isWinningMove(Board &board, char symbol) const
{
    int size = board.getSize();
    // Check if the four corners are occupied by the symbol
    return (board.getCellSymbol(0, 0) == symbol &&
            board.getCellSymbol(0, size - 1) == symbol &&
            board.getCellSymbol(size - 1, 0) == symbol &&
            board.getCellSymbol(size - 1, size - 1) == symbol);
}