#include "deck.h"
#include <ctime>
#include <iostream>

// Default constructor
Deck::Deck()
{
    buildDeck();
    shuffleDeck();
}

// Destructor
Deck::~Deck()
{
    for (Card* card : deckOfCards)
    {
        delete card;
    }
    deckOfCards.clear();
}

// Build a deck with 2 full sets of 52 cards
void Deck::buildDeck()
{
    static const std::string suits[] = {"Spades", "Hearts", "Diamonds", "Clubs"};

    // Build two decks
    for (int deckCount = 0; deckCount < 2; ++deckCount)
    {
        for (const std::string& suit : suits)
        {
            for (int rank = 1; rank <= 13; ++rank)
            {
                deckOfCards.push_back(new Card(rank, suit));
            }
        }
    }
}

// Shuffle the deck
void Deck::shuffleDeck()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = deckOfCards.size() - 1; i > 0; --i)
    {
        int j = std::rand() % (i + 1);
        std::swap(deckOfCards[i], deckOfCards[j]);
    }
}

// Deal one card from the top of the deck
Card* Deck::dealCard()
{
    if (isEmpty())
    {
        return nullptr;
    }

    Card* dealtCard = deckOfCards.back();
    deckOfCards.pop_back();
    return dealtCard;
}

// Check if deck is empty
bool Deck::isEmpty() const
{
    return deckOfCards.empty();
}

// Get the current size of the deck
int Deck::getDeckSize() const
{
    return static_cast<int>(deckOfCards.size());
}
