#include "Board.h"

// Constructor: initialize the board's grid.
Board::Board(int size)
{
    this->size = size;

    // Create a size x size grid
    grid.resize(size, std::vector<Grid>(size));

    // Initialize each grid cell with its coordinates.
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            grid[i][j] = Grid(i, j);
        }
    }
}

// API to return the cell symbol
char Board::getCellSymbol(int row, int col) const
{
    if (row < 0 || row >= size || col < 0 || col >= size)
        return '?';

    if (grid[row][col].occupant != nullptr)
        return grid[row][col].occupant->getSymbol();

    return '-';
}

// API to return the cell Player
Player *Board::getCellPlayer(int row, int col) const
{
    if (row < 0 || row >= size || col < 0 || col >= size)
        return nullptr;

    if (grid[row][col].occupant != nullptr)
        return grid[row][col].occupant;

    return nullptr;
}

// Check if the board is completely filled (no cell available).
bool Board::isFull() const
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            // aternatively you can check for state: grid[i][j].state == GridState::AVAILABLE
            if (grid[i][j].occupant == nullptr)
                return false;
        }
    }
    return true;
}

bool Board::updateGrid(int row, int col, char symbol, Player *occupant)
{
    if (row < 0 || row >= size || col < 0 || col >= size)
        return false;

    // Check if the cell is already occupied
    if (grid[row][col].occupant != nullptr)
    {
        if (symbol == '-') // this is for undo option. when previous sym is fetched, it will be '-'
        {
            grid[row][col].occupant = nullptr;
            grid[row][col].state = GridState::AVAILABLE;
        }
        return false;
    }

    // Update the cell: mark it as not available and set the occupant pointer.
    grid[row][col].occupant = occupant;
    grid[row][col].state = GridState::NOT_AVAILABLE;

    return true;
}

// Display the board grid with larger spaces inside each cell.
void Board::displayGrid() const
{
    // Column Numbers
    std::cout << "    ";
    for (int j = 0; j < size; ++j)
    {
        std::cout << "  " << j << "   ";
    }
    std::cout << std::endl;

    // Top Border
    std::cout << "   ";
    for (int j = 0; j < size; ++j)
    {
        std::cout << "------";
    }
    std::cout << "-" << std::endl;

    for (int i = 0; i < size; ++i)
    {
        // Print row number
        std::cout << " " << i << " |";

        for (int j = 0; j < size; ++j)
        {
            // Print cell contents with extra space
            if (grid[i][j].occupant != nullptr)
            {
                std::cout << "  " << grid[i][j].occupant->getSymbol() << "  ";
            }
            else
            {
                std::cout << "     ";
            }
            std::cout << "|"; // Vertical boundary
        }
        std::cout << std::endl;

        // Row Separator
        std::cout << "   ";
        for (int j = 0; j < size; ++j)
        {
            std::cout << "------";
        }
        std::cout << "-" << std::endl;
    }
}