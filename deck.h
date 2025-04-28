#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>
#include <random>
#include <algorithm>

class Deck
{
private:
    std::vector<Card*> deckOfCards; // Stores 104 cards (2 decks)

public:
    // Default constructor
    Deck();

    // Destructor
    ~Deck();

    // Initialize deck with two full sets of 52 cards
    void buildDeck();

    // Shuffle the deck
    void shuffleDeck();

    // Deal one card from the top of the deck
    Card* dealCard();

    // Check if deck is empty
    bool isEmpty() const;

    // Get the current size of the deck
    int getDeckSize() const;
};

#endif 
