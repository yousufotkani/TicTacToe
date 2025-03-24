#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include "Grid.h"
#include "Player.h"

class Board
{
private:
    int size;
    std::vector<std::vector<Grid>> grid;

public:
    // Constructor: create a board with given size.
    Board(int size);

    int getSize() { return size; }

    // Display the board grid.
    void displayGrid() const;

    // Update a cell at (row, col) with the given symbol.
    // Returns true if update is successful, false otherwise.
    bool updateGrid(int row, int col, char symbol, Player *occupant);

    // Get the symbol at cell (row, col).
    // For simplicity, we assume that if a cell is not occupied, it returns '-'
    // (or you can choose another convention).
    char getCellSymbol(int row, int col) const;

    Player *getCellPlayer(int row, int col) const;

    // Check if the board is completely filled.
    bool isFull() const;
};

#endif // BOARD_H
