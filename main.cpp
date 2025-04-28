#include "game.h"
#include <iostream>
#include <limits>
using namespace std;

// Function prototypes
void displayMenu();
int getMenuChoice();

int main()
{
    Game game;
    bool running = true;

    cout << "\n====================================\n";
    cout << "      Welcome to Forty Thieves!     \n";
    cout << "====================================\n\n";

    while (running)
    {
        displayMenu();
        int choice = getMenuChoice();

        switch (choice)
        {
        case 1:
            game.startGame();
            cout << "\nNew game started!\n";
            game.displayBoard();
            break;
        case 2:
            game.drawCard();
            game.displayBoard();
            if (game.checkWinCondition())
            {
                cout << "\n🎉 Congratulations! You have completed Forty Thieves! 🎉\n";
                running = false;
            }
            break;
        case 3:
        {
            int fromCol, toCol;
            cout << "Enter move as 'from to' (e.g., 3 7): ";
            cin >> fromCol >> toCol;
            if (fromCol >= 1 && fromCol <= 10 && toCol >= 1 && toCol <= 10)
            {
                try
                {
                    game.moveTableauToTableau(fromCol - 1, toCol - 1);
                }
                catch (const exception& e)
                {
                    cout << "\nError: " << e.what() << "\n";
                }
            }
            else
            {
                cout << "\nInvalid column numbers.\n";
            }
            game.displayBoard();
            if (game.checkWinCondition())
            {
                cout << "\n🎉 Congratulations! You have completed Forty Thieves! 🎉\n";
                running = false;
            }
            break;
        }
        case 4:
        {
            int fromCol;
            cout << "Enter source column (1-10) to move to foundations: ";
            cin >> fromCol;
            if (fromCol >= 1 && fromCol <= 10)
            {
                try
                {
                    game.moveTableauToFoundation(fromCol - 1);
                }
                catch (const exception& e)
                {
                    cout << "\nError: " << e.what() << "\n";
                }
            }
            else
            {
                cout << "\nInvalid column number.\n";
            }
            game.displayBoard();
            if (game.checkWinCondition())
            {
                cout << "\n🎉 Congratulations! You have completed Forty Thieves! 🎉\n";
                running = false;
            }
            break;
        }
        case 5:
        {
            int toCol;
            cout << "Enter destination column (1-10) for the waste card: ";
            cin >> toCol;
            if (toCol >= 1 && toCol <= 10)
            {
                try
                {
                    game.moveWasteToTableau(toCol - 1);
                }
                catch (const exception& e)
                {
                    cout << "\nError: " << e.what() << "\n";
                }
            }
            else
            {
                cout << "\nInvalid column number.\n";
            }
            game.displayBoard();
            if (game.checkWinCondition())
            {
                cout << "\n🎉 Congratulations! You have completed Forty Thieves! 🎉\n";
                running = false;
            }
            break;
        }
        case 6:
            try
            {
                game.moveWasteToFoundation();
            }
            catch (const exception& e)
            {
                cout << "\nError: " << e.what() << "\n";
            }
            game.displayBoard();
            if (game.checkWinCondition())
            {
                cout << "\n🎉 Congratulations! You have completed Forty Thieves! 🎉\n";
                running = false;
            }
            break;
        case 7:
            game.displayBoard();
            break;
        case 8:
            game.restartGame();
            cout << "\nGame restarted!\n";
            game.displayBoard();
            break;
        case 9:
            running = false;
            cout << "\nThanks for playing Forty Thieves!\n";
            break;
        default:
            cout << "\nInvalid choice.\n";
            break;
        }

        cout << "\n\n";
    }

    return 0;
}

// Display the main menu
void displayMenu()
{
    cout << "\n==== Forty Thieves Solitaire ====" << endl;
    cout << "1. Start New Game" << endl;
    cout << "2. Draw Card" << endl;
    cout << "3. Move Tableau to Tableau" << endl;
    cout << "4. Move Tableau to Foundation" << endl;
    cout << "5. Move Waste to Tableau" << endl;
    cout << "6. Move Waste to Foundation" << endl;
    cout << "7. View Current Board" << endl;
    cout << "8. Restart Game" << endl;
    cout << "9. Exit" << endl;
    cout << "Choose an option: ";
}

// Safely get the menu choice from user
int getMenuChoice()
{
    int choice;
    while (!(cin >> choice))
    {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}
