#include <iostream>
#include <vector>
#include <cctype>  // for toupper()
#include <cstdlib> // for rand(), srand()
#include <ctime>   // for time()
#include "Game.h"  // Game class declaration
#include "Player.h"

// Utility function to display ASCII art welcome message.
void printWelcomeArt()
{
    std::cout << "=================================\n";
    std::cout << "      WELCOME TO TICTACTOE       \n";
    std::cout << "=================================\n\n";
}

// Utility function to check if a symbol is already in use by any player.
bool symbolAlreadyUsed(const std::vector<Player *> &players, char symbol)
{
    for (const auto &player : players)
    {
        if (player->getSymbol() == symbol)
            return true;
    }
    return false;
}

// Utility function to select a random starting player index.
int getRandomStartingPlayer(int numPlayers)
{
    return rand() % numPlayers;
}

int main()
{
    // Seed the random number generator.
    srand(static_cast<unsigned int>(time(nullptr)));

    // 1. Display welcome ASCII art.
    printWelcomeArt();

    char playAgain = 'Y';
    while (std::toupper(playAgain) == 'Y')
    {
        // 2. Request board size from the player.
        int boardSize;
        std::cout << "Enter board size (max 10): ";
        std::cin >> boardSize;
        if (boardSize < 3)
            boardSize = 3;
        else if (boardSize > 10)
            boardSize = 10;

        // 3. Request number of players.
        int numPlayers;
        std::cout << "Enter number of players: ";
        do
        {
            std::cin >> numPlayers;
            if (numPlayers >= boardSize)
            {
                std::cout << "No of players should not be greater or equal to board size. Enter a lesser value: ";
            }
        } while (numPlayers >= boardSize);

        // 4. Dynamically allocate the Game object.
        Game *game = new Game(boardSize);

        // 5. Loop for each player to get name and symbol.
        for (int i = 0; i < numPlayers; ++i)
        {
            std::string name;
            char symbol;
            std::cout << "\nEnter name for player " << i + 1 << ": ";
            std::cin >> name;
            bool validSymbol = false;
            do
            {
                std::cout << "Enter symbol for " << name << " (a-z): ";
                std::cin >> symbol;
                symbol = std::toupper(symbol); // Convert to uppercase.
                if (symbol < 'A' || symbol > 'Z')
                {
                    std::cout << "Symbol must be in the range A-Z. Try again.\n";
                }
                else if (symbolAlreadyUsed(game->getPlayers(), symbol))
                {
                    std::cout << "Symbol '" << symbol << "' already in use. Choose another.\n";
                }
                else
                {
                    validSymbol = true;
                }
            } while (!validSymbol);

            // Create a HumanPlayer and add to the game.
            game->addPlayer(new HumanPlayer(name, symbol));
        }

        // 6. If only one player is provided, add a BotPlayer.
        if (numPlayers == 1)
        {
            char humanSymbol = game->getPlayers()[0]->getSymbol();
            // Choose a random symbol for the bot that is not equal to the human player's symbol.
            char botSymbol = 'O';
            if (symbolAlreadyUsed(game->getPlayers(), botSymbol))
            {
                for (char c = 'A'; c <= 'Z'; ++c)
                {
                    if (c != humanSymbol)
                    {
                        botSymbol = c;
                        break;
                    }
                }
            }
            // For simplicity, we set bot difficulty to EASY.
            game->addPlayer(new BotPlayer("Bot", botSymbol, EASY));
            numPlayers = 2; // Update number of players.
        }

        // 7. Start the game.
        game->playGame();

        // Clean up dynamic memory.
        delete game;

        // Ask if the user wants to play again.
        std::cout << "\nDo you want to continue playing? (Y/N): ";
        std::cin >> playAgain;
        std::cout << std::endl;
    }
    return 0;
}
