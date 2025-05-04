/* Program name: Forty Thieves
* Author: Walter Hodgson
* Date last updated: 5/3/2025
* Purpose: Final Project for Data Structures
*/

#include "game.h"
#include <iostream>
#include <limits>

// Function prototypes
void displayMenu(); // Displays the main menu
int getMenuChoice(); // Gets choice from the user

int main()
{
    Game game; // Main Game object
    bool running = true; // Game loop control flag

    std::cout << "\n====================================\n";
    std::cout << "      Welcome to Forty Thieves!     \n";
    std::cout << "====================================\n\n";

    while (running) // Main game loop
    {
        displayMenu();
        int choice = getMenuChoice(); 

        switch (choice) // Switch will drive the menu
        {
        case 1: // Starts a game
            game.startGame();
            std::cout << "\nNew game started!\n";
            game.displayBoard();
            break;
        case 2: // Draws a card from the deck
            game.drawCard();
            game.displayBoard();
            if (game.checkWinCondition())
            {
                std::cout << "\n🎉 Congratulations! You have completed Forty Thieves! 🎉\n";
                running = false;
            }
            break;
        case 3: // Moves a card from one tableau to another one
        {
            int fromCol, toCol;
            std::cout << "Enter move as 'from to' (e.g., 3 7): ";
            std::cin >> fromCol >> toCol;
            if (fromCol >= 1 && fromCol <= 10 && toCol >= 1 && toCol <= 10)
            {
                try
                {
                    game.moveTableauToTableau(fromCol - 1, toCol - 1); // Adjusting indexing
                }
                catch (const std::exception& e)
                {
                    std::cout << "\nError: " << e.what() << "\n";
                }
            }
            else
            {
                std::cout << "\nInvalid column numbers.\n";
            }
            game.displayBoard();
            if (game.checkWinCondition())
            {
                std::cout << "\n🎉 Congratulations! You have completed Forty Thieves! 🎉\n";
                running = false;
            }
            break;
        }
        case 4: // Moves a card from the tableau to the foundation
        {
            int fromCol;
            std::cout << "Enter source column (1-10) to move to foundations: ";
            std::cin >> fromCol;
            if (fromCol >= 1 && fromCol <= 10)
            {
                try
                {
                    game.moveTableauToFoundation(fromCol - 1); // Adjust indexing again
                }
                catch (const std::exception& e)
                {
                    std::cout << "\nError: " << e.what() << "\n";
                }
            }
            else
            {
                std::cout << "\nInvalid column number.\n";
            }
            game.displayBoard();
            if (game.checkWinCondition())
            {
                std::cout << "\n🎉 Congratulations! You have completed Forty Thieves! 🎉\n";
                running = false;
            }
            break;
        }
        case 5: // Move a card from the waste pile to the tableau
        {
            int toCol;
            std::cout << "Enter destination column (1-10) for the waste card: ";
            std::cin >> toCol;
            if (toCol >= 1 && toCol <= 10)
            {
                try
                {
                    game.moveWasteToTableau(toCol - 1);
                }
                catch (const std::exception& e)
                {
                    std::cout << "\nError: " << e.what() << "\n";
                }
            }
            else
            {
                std::cout << "\nInvalid column number.\n";
            }
            game.displayBoard();
            if (game.checkWinCondition())
            {
                std::cout << "\n🎉 Congratulations! You have completed Forty Thieves! 🎉\n";
                running = false;
            }
            break;
        }
        case 6: // Move a card from the waste pile to the foundation
            try
            {
                game.moveWasteToFoundation();
            }
            catch (const std::exception& e)
            {
                std::cout << "\nError: " << e.what() << "\n";
            }
            game.displayBoard();
            if (game.checkWinCondition())
            {
                std::cout << "\n🎉 Congratulations! You have completed Forty Thieves! 🎉\n";
                running = false;
            }
            break;
        case 7: { // Move a card from the tableau to the temporary column - used to move whole columns
            int from;
            std::cout << "Enter source column (1-10) to move card to temp: ";
            std::cin >> from;
            game.moveTableauToTemp(from - 1); // 0-indexed
            break;
        }
        case 8: { // Move a card from the temporary column back to the tableau
            int to;
            std::cout << "Enter destination column (1-10) to move card from temp: ";
            std::cin >> to;
            game.moveTempToTableau(to - 1); 
            break;
        }
        case 9: // Display the current board
            game.displayBoard();
            break;
        case 10: // Display the current board
            game.restartGame(); 
            std::cout << "\nGame restarted!\n";
            game.displayBoard();
            break;
        case 11: // Exit the game
            running = false;
            std::cout << "\nThanks for playing Forty Thieves!\n";
            break;
        default: // Handling invalid choices
            std::cout << "\nInvalid choice.\n";
            break;
        }

        std::cout << "\n\n";
    }

    return 0;
}

// Display the main menu
void displayMenu()
{
    std::cout << "\n==== Forty Thieves Solitaire ====" << std::endl;
    std::cout << "1. Start New Game" << std::endl;
    std::cout << "2. Draw Card" << std::endl;
    std::cout << "3. Move Tableau to Tableau" << std::endl;
    std::cout << "4. Move Tableau to Foundation" << std::endl;
    std::cout << "5. Move Waste to Tableau" << std::endl;
    std::cout << "6. Move Waste to Foundation" << std::endl;
    std::cout << "7. Move Tableau to Temp Column" << std::endl; 
    std::cout << "8. Move Temp Column to Tableau" << std::endl;        
    std::cout << "9. View Current Board" << std::endl;
    std::cout << "10. Restart Game" << std::endl;
    std::cout << "11. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

// Safely get the menu choice from user
int getMenuChoice()
{
    int choice;
    while (!(std::cin >> choice))
    {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}
