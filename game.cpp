#include "game.h"
#include <iomanip>

// Constructor
Game::Game()
{
    deck = new Deck();
    startGame();
}

// Destructor
Game::~Game()
{
    delete deck;
}

// Start a new game
void Game::startGame()
{
    // Deal initial tableau: 4 cards per column
    for (int col = 0; col < 10; ++col)
    {
        for (int row = 0; row < 4; ++row)
        {
            Card* newCard = deck->dealCard();
            if (row == 3) // Last card dealt will be face up
            {
                newCard->setFaceUp(true);
            }
            else
            {
                newCard->setFaceUp(false);
            }
            tableau[col].push(newCard);
        }
    }
}

// Restart the current game
void Game::restartGame()
{
    delete deck;
    deck = new Deck();

    // Clear tableau and foundations
    for (int i = 0; i < 10; ++i)
    {
        while (!tableau[i].isEmptyStack())
        {
            tableau[i].pop();
        }
    }
    for (int i = 0; i < 8; ++i)
    {
        while (!foundations[i].isEmptyStack())
        {
            foundations[i].pop();
        }
    }
    
    // Clear waste pile
    while (!wastePile.isEmptyQueue())
    {
        wastePile.dequeue();
    }

    startGame();
}

// Draw a card from the deck to the waste pile
void Game::drawCard()
{
    Card* newCard = deck->dealCard();
    if (newCard != nullptr)
    {
        newCard->setFaceUp(true);
        wastePile.enqueue(newCard);
    }
    else
    {
        std::cout << "\nNo more cards to draw.\n";
    }
}

// Move a card from tableau to another tableau column
void Game::moveTableauToTableau(int fromCol, int toCol)
{
    if (tableau[fromCol].isEmptyStack())
    {
        std::cout << "\nCannot move from an empty column.\n";
        return;
    }

    Card* movingCard = tableau[fromCol].top();

    if (tableau[toCol].isEmptyStack())
    {
        tableau[toCol].push(movingCard);
        tableau[fromCol].pop();
    }
    else
    {
        Card* destinationCard = tableau[toCol].top();
        if (isMoveValid(movingCard, destinationCard))
        {
            tableau[toCol].push(movingCard);
            tableau[fromCol].pop();
        }
        else
        {
            std::cout << "\nInvalid move.\n";
        }
    }

    // If card revealed on source column, flip it to face up
    if (!tableau[fromCol].isEmptyStack())
    {
        Card* newTop = tableau[fromCol].top();
        if (!newTop->isFaceUp())
        {
            newTop->flipCard();
        }
    }
}

// Move a card from tableau to foundations
void Game::moveTableauToFoundation(int fromCol)
{
    if (tableau[fromCol].isEmptyStack())
    {
        std::cout << "\nCannot move from an empty column.\n";
        return;
    }

    Card* movingCard = tableau[fromCol].top();
    int foundationIndex = findFoundationIndex(movingCard->getSuit());

    if (foundationIndex != -1)
    {
        if (foundations[foundationIndex].isEmptyStack() && movingCard->getRank() == 1)
        {
            foundations[foundationIndex].push(movingCard);
            tableau[fromCol].pop();
        }
        else if (!foundations[foundationIndex].isEmptyStack())
        {
            Card* topFoundation = foundations[foundationIndex].top();
            if (topFoundation->getRank() + 1 == movingCard->getRank())
            {
                foundations[foundationIndex].push(movingCard);
                tableau[fromCol].pop();
            }
            else
            {
                std::cout << "\nInvalid move to foundation.\n";
            }
        }
    }
}

// Move a card from waste pile to tableau
void Game::moveWasteToTableau(int toCol)
{
    if (wastePile.isEmptyQueue())
    {
        std::cout << "\nNo cards in waste pile.\n";
        return;
    }

    Card* movingCard = wastePile.front();

    if (tableau[toCol].isEmptyStack())
    {
        tableau[toCol].push(movingCard);
        wastePile.dequeue();
    }
    else
    {
        Card* destinationCard = tableau[toCol].top();
        if (isMoveValid(movingCard, destinationCard))
        {
            tableau[toCol].push(movingCard);
            wastePile.dequeue();
        }
        else
        {
            std::cout << "\nInvalid move to tableau.\n";
        }
    }
}

// Move a card from waste pile to foundations
void Game::moveWasteToFoundation()
{
    if (wastePile.isEmptyQueue())
    {
        std::cout << "\nNo cards in waste pile.\n";
        return;
    }

    Card* movingCard = wastePile.front();
    int foundationIndex = findFoundationIndex(movingCard->getSuit());

    if (foundationIndex != -1)
    {
        if (foundations[foundationIndex].isEmptyStack() && movingCard->getRank() == 1)
        {
            foundations[foundationIndex].push(movingCard);
            wastePile.dequeue();
        }
        else if (!foundations[foundationIndex].isEmptyStack())
        {
            Card* topFoundation = foundations[foundationIndex].top();
            if (topFoundation->getRank() + 1 == movingCard->getRank())
            {
                foundations[foundationIndex].push(movingCard);
                wastePile.dequeue();
            }
            else
            {
                std::cout << "\nInvalid move to foundation.\n";
            }
        }
    }
}

// Display the full game board
/* V1 no ASCII art
void Game::displayBoard() const
{
    std::cout << "\nFoundations:\n";
    for (int i = 0; i < 8; ++i)
    {
        if (!foundations[i].isEmptyStack())
        {
            foundations[i].top()->displayCard(std::cout);
        }
        else
        {
            std::cout << "[  ]";
        }
        std::cout << " ";
    }

    std::cout << "\n\nWaste Pile: ";
    if (!wastePile.isEmptyQueue())
    {
        wastePile.front()->displayCard(std::cout);
    }
    else
    {
        std::cout << "[  ]";
    }

    std::cout << "    Draw Pile: ";
    if (!deck->isEmpty())
    {
        std::cout << "[ ## ]";
    }
    else
    {
        std::cout << "[  ]";
    }

    std::cout << "\n\nTableau:\n";
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Col " << i + 1 << "\t";
    }
    std::cout << "\n";
}
*/

// Version 2 trying ASCII art
void Game::displayBoard() const
{
    using namespace std;
    
    cout << "\nFoundations:\n";
    for (int i = 0; i < 8; ++i)
    {
        if (!foundations[i].isEmptyStack())
            foundations[i].top()->displayCard(cout);
        else
            cout << "[  ]";
        cout << " ";
    }
    
    cout << "\n\nWaste Pile: ";
    if (!wastePile.isEmptyQueue())
        wastePile.front()->displayCard(cout);
    else
        cout << "[  ]";
    
    cout << "    Draw Pile: ";
    if (!deck->isEmpty())
        cout << "[ ## ]";
    else
        cout << "[  ]";

    cout << "\n\nTableau Columns:\n";
    
    // Print column headers
    for (int i = 0; i < 10; ++i)
    {
        cout << "Col " << i+1 << "\t";
    }
    cout << "\n";

    // Find the maximum column height
    int maxHeight = 0;
    for (int i = 0; i < 10; ++i)
    {
        int height = 0;
        linkedStack<Card*> tempStack = tableau[i];
        while (!tempStack.isEmptyStack())
        {
            tempStack.pop();
            ++height;
        }
        if (height > maxHeight)
            maxHeight = height;
    }

    // Print row by row
    for (int row = maxHeight; row > 0; --row)
    {
        for (int col = 0; col < 10; ++col)
        {
            linkedStack<Card*> tempStack;
            linkedStack<Card*> originalStack = tableau[col];
            
            // Reverse the stack to access bottom to top
            while (!originalStack.isEmptyStack())
            {
                tempStack.push(originalStack.top());
                originalStack.pop();
            }

            int tempHeight = 0;
            linkedStack<Card*> tempCopy = tempStack;
            while (!tempCopy.isEmptyStack())
            {
                tempCopy.pop();
                ++tempHeight;
            }

            if (tempHeight >= row)
            {
                // Get the correct card
                int cardsToSkip = tempHeight - row;
                for (int skip = 0; skip < cardsToSkip; ++skip)
                {
                    tempStack.pop();
                }
                if (!tempStack.isEmptyStack())
                {
                    tempStack.top()->displayCard(cout);
                }
                else
                {
                    cout << "[  ]";
                }
            }
            else
            {
                cout << "     "; // Empty space if no card
            }
            
            cout << "\t";
        }
        cout << "\n";
    }
}

// Check if move is valid between two tableau cards
bool Game::isMoveValid(Card* movingCard, Card* destinationCard) const
{
    if (movingCard == nullptr || destinationCard == nullptr)
    {
        return false;
    }

    return (movingCard->getSuit() == destinationCard->getSuit()) &&
           (movingCard->getRank() + 1 == destinationCard->getRank());
}

// Find foundation index based on suit
int Game::findFoundationIndex(const std::string& suit) const
{
    if (suit == "Spades")
        return 0;
    else if (suit == "Hearts")
        return 1;
    else if (suit == "Diamonds")
        return 2;
    else if (suit == "Clubs")
        return 3;
    else
        return -1;
}

// Checking for win state
bool Game::checkWinCondition() const
{
    for (int i = 0; i < 8; ++i)
    {
        if (foundations[i].isEmptyStack() || foundations[i].top()->getRank() != 13)
            return false;
    }
    return true;
}
