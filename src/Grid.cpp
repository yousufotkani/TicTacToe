#include "Grid.h"

// Default constructor: sets row and col to 0, state AVAILABLE, no occupant.
Grid::Grid()
{
    this->row = 0;
    this->col = 0;
    this->state = GridState::AVAILABLE;
    occupant = nullptr;
}

// Parameterized constructor: initialize coordinates, state AVAILABLE, and no occupant.
Grid::Grid(int row, int col)
{
    this->row = row;
    this->col = col;
    this->state = GridState::AVAILABLE;
    occupant = nullptr;
}