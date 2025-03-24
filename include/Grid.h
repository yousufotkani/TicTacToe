#ifndef GRID_H
#define GRID_H

// Forward declaration for Player if needed in Grid.
// (Assuming Player is defined elsewhere)
class Player;

enum class GridState
{
    AVAILABLE,
    NOT_AVAILABLE,
    BLOCKED
};

class Grid
{
public:
    int row;
    int col;
    GridState state;
    Player *occupant; // Pointer to the player occupying the grid cell; nullptr if none

    // Constructors
    Grid();
    Grid(int row, int col);
};

#endif // GRID_H
