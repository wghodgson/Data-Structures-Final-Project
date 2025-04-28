#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "linkedStack.h"
#include "linkedQueue.h"
#include <iostream>
#include <string>

class Game
{
private:
    Deck* deck; // Main deck of 104 cards
    linkedQueue<Card*> wastePile; // Waste pile (drawn cards)
    linkedStack<Card*> foundations[8]; // Eight foundation piles
    linkedStack<Card*> tableau[10]; // Ten tableau columns

public:
    // Constructor and Destructor
    Game();
    ~Game();

    // Start a new game
    void startGame();

    // Restart the current game
    void restartGame();

    // Draw a card from the deck to the waste pile
    void drawCard();

    // Move a card from tableau to another tableau column
    void moveTableauToTableau(int fromCol, int toCol);

    // Move a card from tableau to foundations
    void moveTableauToFoundation(int fromCol);

    // Move a card from waste pile to tableau or foundations
    void moveWasteToTableau(int toCol);
    void moveWasteToFoundation();

    // Display the full game board using ASCII art
    void displayBoard() const;

    // Helper methods
    bool isMoveValid(Card* movingCard, Card* destinationCard) const;
    int findFoundationIndex(const std::string& suit) const;

    // Win detection
    bool checkWinCondition() const;
};

#endif 
