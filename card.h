#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

class Card
{
private:
    int rank;           // 1 = Ace, 11 = Jack, 12 = Queen, 13 = King
    std::string suit;   // "Spades", "Hearts", "Diamonds", "Clubs"
    std::string color;  // "Red" or "Black"
    bool faceUp;        // true = visible, false = hidden

public:
    // Default constructor
    Card();

    // Constructor with parameters
    Card(int cardRank, const std::string& cardSuit);

    // Accessor methods
    int getRank() const;
    std::string getSuit() const;
    std::string getColor() const;
    bool isFaceUp() const;

    // Mutator methods
    void flipCard(); // Flips card faceUp or faceDown
    void setFaceUp(bool isFaceUp); // Explicitly sets to faceUp

    // Display method
    void displayCard(std::ostream& out) const;
};

#endif 
