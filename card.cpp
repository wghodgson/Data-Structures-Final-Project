#include "card.h"
#include <iostream>
#include <iomanip>

// Default constructor
Card::Card()
{
    rank = 0;
    suit = "";
    color = "";
    faceUp = false;
}

// Constructor with parameters
Card::Card(int cardRank, const std::string& cardSuit)
{
    rank = cardRank;
    suit = cardSuit;
    faceUp = false; // Default to face down until set later

    // Set color based on suit
    if (suit == "Hearts" || suit == "Diamonds")
        color = "Red";
    else
        color = "Black";
}

// Accessor methods
int Card::getRank() const
{
    return rank;
}

std::string Card::getSuit() const
{
    return suit;
}

std::string Card::getColor() const
{
    return color;
}

bool Card::isFaceUp() const
{
    return faceUp;
}

// Mutator methods
void Card::flipCard()
{
    faceUp = !faceUp;
}

void Card::setFaceUp(bool isFaceUp)
{
    faceUp = isFaceUp;
}

// Display method
void Card::displayCard(std::ostream& out) const
{
    if (faceUp)
    {
        std::string rankStr;

        switch (rank)
        {
        case 1:
            rankStr = "A";
            break;
        case 11:
            rankStr = "J";
            break;
        case 12:
            rankStr = "Q";
            break;
        case 13:
            rankStr = "K";
            break;
        default:
            rankStr = std::to_string(rank);
        }

        // Output format: [RankSuitInitial]
        out << "[" << std::setw(2) << rankStr[0] << suit[0] << "]";
    }
    else
    {
        out << "[XX]";
    }
}
