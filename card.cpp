#include "card.h"
#include <iostream>
#include <iomanip>

// Default constructor 
Card::Card()
{
    rank = 0; // Initialize rank
    suit = ""; // Initialize no suit
    color = ""; // Initialize with no color
    faceUp = false; // Sets it to face down
}

// Constructor with parameters 
Card::Card(int cardRank, const std::string& cardSuit)
{
    rank = cardRank; // Initializes with rank
    suit = cardSuit; // Initializes with suit
    faceUp = false; // Default to face down until set later

    // Set color based on suit
    if (suit == "Hearts" || suit == "Diamonds")
        color = "Red";
    else
        color = "Black";
}

// Accessor method to get card rank
int Card::getRank() const
{
    return rank;
}
// Accessor method to get card suit
std::string Card::getSuit() const
{
    return suit;
}
// Accessor method to get card color
std::string Card::getColor() const
{
    return color;
}
// Returns whether card is face up
bool Card::isFaceUp() const
{
    return faceUp;
}

// Will toggle the card face up and down
void Card::flipCard()
{
    faceUp = !faceUp;
}
// Setting whether the card is face up
void Card::setFaceUp(bool isFaceUp)
{
    faceUp = isFaceUp;
}

// Display method will show XX if face down or the rank and suit symbol
void Card::displayCard(std::ostream& out) const
{
    if (!faceUp)
    {
        out << "[XX]";
        return;
    }

    std::string rankStr;
    switch (rank)
    {
    case 1:  rankStr = " A"; break;
    case 11: rankStr = " J"; break;
    case 12: rankStr = " Q"; break;
    case 13: rankStr = " K"; break;
    default:
        rankStr = (rank < 10 ? " " : "") + std::to_string(rank); // Adding a space so I keep columns straight
    }
    // Converting the suit name to a symbol for display
    std::string suitSymbol;
    if (suit == "Hearts")
        suitSymbol = "♥";
    else if (suit == "Diamonds")
        suitSymbol = "♦";
    else if (suit == "Clubs")
        suitSymbol = "♣";
    else if (suit == "Spades")
        suitSymbol = "♠";
    else
        suitSymbol = "?"; // In case of invalid suit

    out << "[" << rankStr << suitSymbol << "]";
}
// Returns true if the card is red
bool Card::isRed() const
{
    return color == "Red";
}
