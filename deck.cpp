#include "deck.h"
#include <ctime>
#include <iostream>

// Default constructor builds and shuffles deck when deck object created
Deck::Deck()
{
    buildDeck(); // Create a 104 card deck (Game I picked requires 2 decks)
    shuffleDeck(); // Shuffle after building
}

// Destructor to clean up memory
Deck::~Deck()
{
    for (Card* card : deckOfCards)
    {
        delete card; // Deleting card pointer
    }
    deckOfCards.clear(); // Clear to remove any dangling pointers
}

// Build a deck with 2 full sets of 52 cards
void Deck::buildDeck()
{
    static const std::string suits[] = {"Spades", "Hearts", "Diamonds", "Clubs"};

    // Looping twice to simulate two card decks
    for (int deckCount = 0; deckCount < 2; ++deckCount)
    {
        for (const std::string& suit : suits)
        {
            for (int rank = 1; rank <= 13; ++rank)
            {
                deckOfCards.push_back(new Card(rank, suit)); // Dynamically allocate a card with the current rank and suit
            }
        }
    }
}

// Shuffle the deck uses an algorithm called Fisher-Yates ... Youtube has good tutorials
void Deck::shuffleDeck()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed RNG
    for (int i = deckOfCards.size() - 1; i > 0; --i)
    {
        int j = std::rand() % (i + 1); // Pick a random index
        std::swap(deckOfCards[i], deckOfCards[j]); // Swap the current card with the random one
    }
}

// Deal one card from the top of the deck
Card* Deck::dealCard()
{
    if (isEmpty())
    {
        return nullptr; // Returns nullptr if deck is empty
    }

    Card* dealtCard = deckOfCards.back(); // Get the last card
    deckOfCards.pop_back(); // Remove it from the deck
    return dealtCard; // Return the card pointer
}

// Check if deck is empty
bool Deck::isEmpty() const
{
    return deckOfCards.empty(); // Returns true if no cards are left
}

// Get the current size of the deck
int Deck::getDeckSize() const
{
    return static_cast<int>(deckOfCards.size());
}
