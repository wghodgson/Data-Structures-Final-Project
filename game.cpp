#include "game.h"
#include <iomanip>

// Constructor initializes a new deck that has been shuffled
Game::Game()
{
    deck = new Deck();
}

// Destructor to clean up the dynamically allocated deck
Game::~Game()
{
    delete deck;
}

//Helper returns the most recently added card in waste
Card* Game::getLastWasteCard() const {
    return wastePile.isEmptyQueue() ? nullptr : wastePile.back();
}

// Helper to remove the most recently added card in waste pile
void Game::removeLastWasteCard()
{
    if (wastePile.isEmptyQueue()) return;

    linkedQueue<Card*> tempQueue;

    // Move all but last to temp
    while (wastePile.length() > 1)
    {
        tempQueue.enqueue(wastePile.front());
        wastePile.dequeue(); 
    }

    // Discard the last card
    wastePile.dequeue();

    // Restore all the cards except the last one that was just removed
    while (!tempQueue.isEmptyQueue())
    {
        wastePile.enqueue(tempQueue.front());
        tempQueue.dequeue();
    }
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
    for (int i = 0; i < 8; ++i) // Clear the foundation piles
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

    startGame(); // Deal a fresh game
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

// Move a card from tableau to another tableau column as long as it is a valid move
void Game::moveTableauToTableau(int fromCol, int toCol)
{
    if (tableau[fromCol].isEmptyStack())
    {
        std::cout << "\nCannot move from an empty column.\n";
        return;
    }

    Card* movingCard = tableau[fromCol].top();

    if (!movingCard->isFaceUp())
    {
        std::cout << "\nCannot move a face-down card.\n";
        return;
    }
    // If the column is empty then allow the move
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
            return;
        }
    }

    // Flip card face up if the card is now exposed
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
    if (tableau[fromCol].isEmptyStack()) // Prevent move from an empty column
    {
        std::cout << "\nCannot move from an empty column.\n";
        return;
    }

    Card* movingCard = tableau[fromCol].top();
    bool moved = false;
    // Try placing the card on one of the foundation piles
    for (int i = 0; i < 8; ++i)
    {
        if (foundations[i].isEmptyStack())
        {
            if (movingCard->getRank() == 1) // Only allow the ace to start the foundation
            {
                foundations[i].push(movingCard);
                tableau[fromCol].pop();
                moved = true;
                break;
            }
        }
        else
        {
            Card* topCard = foundations[i].top();
            if (topCard->getSuit() == movingCard->getSuit() && // Check if card is same suit and adds one to rank
                topCard->getRank() + 1 == movingCard->getRank())
            {
                foundations[i].push(movingCard);
                tableau[fromCol].pop();
                moved = true;
                break;
            }
        }
    }

    if (!moved)
    {
        std::cout << "\nInvalid move to foundation.\n";
    }
    else
    {
        // Flip next card in tableau column if needed
        if (!tableau[fromCol].isEmptyStack())
        {
            Card* newTop = tableau[fromCol].top();
            if (!newTop->isFaceUp())
            {
                newTop->flipCard();
            }
        }
    }
}

// Move a card from waste pile to tableau
void Game::moveWasteToTableau(int toCol)
{
    if (wastePile.isEmptyQueue())
    {
        std::cout << "\nWaste pile is empty.\n";
        return;
    }

    Card* movingCard = getLastWasteCard(); // Get the most recent draw (back of queue)

    if (!movingCard->isFaceUp())
    {
        std::cout << "\nCannot move a face-down card from waste.\n";
        return;
    }

    if (tableau[toCol].isEmptyStack()) // Allows any card on an empty tableau column
    {
        tableau[toCol].push(movingCard);
        removeLastWasteCard(); // Removes from back
    }
    else
    {
        Card* destinationCard = tableau[toCol].top();
        if (isMoveValid(movingCard, destinationCard))
        {
            tableau[toCol].push(movingCard);
            removeLastWasteCard();
        }
        else
        {
            std::cout << "\nInvalid move to tableau.\n";
        }
    }
}

// Move a card from waste pile to foundations if valid
void Game::moveWasteToFoundation()
{
    if (wastePile.isEmptyQueue())
    {
        std::cout << "\nNo cards in waste pile.\n";
        return;
    }

    Card* movingCard = getLastWasteCard(); // Using helper to get the correct card
    bool moved = false;
    // Attempting to place a card into a foundation slot
    for (int i = 0; i < 8; ++i)
    {
        if (foundations[i].isEmptyStack())
        {
            if (movingCard->getRank() == 1) // Ace
            {
                foundations[i].push(movingCard);
                removeLastWasteCard();
                moved = true;
                break;
            }
        }
        else
        {
            Card* topCard = foundations[i].top();
            if (topCard->getSuit() == movingCard->getSuit() &&
                topCard->getRank() + 1 == movingCard->getRank())
            {
                foundations[i].push(movingCard);
                removeLastWasteCard();
                moved = true;
                break;
            }
        }
    }

    if (!moved)
    {
        std::cout << "\nInvalid move to foundation.\n";
    }
}
// Move one card from the tableau to a temporary column for gameplay
void Game::moveTableauToTemp(int fromCol)
{
    if (fromCol < 0 || fromCol >= 10) // Validate column index
    {
        std::cout << "\nInvalid column number.\n";
        return;
    }

    if (tableau[fromCol].isEmptyStack())
    {
        std::cout << "\nCannot move from an empty column.\n";
        return;
    }

    Card* topCard = tableau[fromCol].top();
    // Only allow the face up cards to move
    if (!topCard->isFaceUp())
    {
        std::cout << "\nCannot move a face-down card.\n";
        return;
    }

    // Move the card to the temp column
    tempColumn.push(topCard);
    tableau[fromCol].pop();

    std::cout << "\nMoved ";
    topCard->displayCard(std::cout);
    std::cout << " to temporary column.\n";

    // Flip the next card if needed
    if (!tableau[fromCol].isEmptyStack())
    {
        Card* newTop = tableau[fromCol].top();
        if (!newTop->isFaceUp())
        {
            newTop->flipCard();
        }
    }

    // Display board
    displayBoard();
}
// Moving a card from the temporary column back to the tableau
void Game::moveTempToTableau(int toCol)
{
    if (toCol < 0 || toCol >= 10)
    {
        std::cout << "\nInvalid destination column.\n";
        return;
    }

    if (tempColumn.isEmptyStack())
    {
        std::cout << "\nTemporary column is empty.\n";
        return;
    }

    Card* movingCard = tempColumn.top();

    if (tableau[toCol].isEmptyStack())
    {
        tableau[toCol].push(movingCard);
        tempColumn.pop();
        std::cout << "\nMoved ";
        movingCard->displayCard(std::cout);
        std::cout << " to Column " << (toCol + 1) << ".\n";
        return;
    }

    Card* destinationCard = tableau[toCol].top();

    if (isMoveValid(movingCard, destinationCard))
    {
        tableau[toCol].push(movingCard);
        tempColumn.pop();
        std::cout << "\nMoved ";
        movingCard->displayCard(std::cout);
        std::cout << " to Column " << (toCol + 1) << ".\n";
    }
    else
    {
        std::cout << "\nInvalid move from temp column to Column " << (toCol + 1) << ".\n";
    }

    // Display board
    displayBoard();
}

// Print the current game board - foundation, waste, draw, temp and tableau
void Game::displayBoard() const
{   
    std::cout << "\nFoundations:\n"; // Foundations
    for (int i = 0; i < 8; ++i)
    {
        if (!foundations[i].isEmptyStack())
            foundations[i].top()->displayCard(std::cout);
        else
            std::cout << "[  ]";
        std::cout << " ";
    }
    
    std::cout << "\n\nWaste Pile: "; // Waste and draw piles
    Card* lastWasteCard = getLastWasteCard();
    if (lastWasteCard != nullptr)
        lastWasteCard->displayCard(std::cout);
    else
        std::cout << "[  ]";
    
    std::cout << "    Draw Pile: ";
    if (!deck->isEmpty())
        std::cout << "[ ## ]";
    else
        std::cout << "[  ]";

    std::cout << "    Temp Column: "; // Temp column
    linkedStack<Card*> tempCopy = tempColumn;
    linkedStack<Card*> displayStack;
        
    // Reverse for left-to-right display
    while (!tempCopy.isEmptyStack())
        displayStack.push(tempCopy.pop());
        
    while (!displayStack.isEmptyStack())
    {
        Card* card = displayStack.pop();
        card->displayCard(std::cout);
        std::cout << " ";
    }

    std::cout << "\n\nTableau Columns:\n"; // Tableau
    
    // Print column headers
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Col " << i+1 << "\t";
    }
    std::cout << "\n";

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
                    tempStack.top()->displayCard(std::cout);
                }
                else
                {
                    std::cout << "[  ]";
                }
            }
            else
            {
                std::cout << "     "; // Empty space if no card
            }
            
            std::cout << "\t";
        }
        std::cout << "\n";
    }
}

// Check if move is valid between two tableau cards
bool Game::isMoveValid(Card* movingCard, Card* destinationCard) const
{
    if (movingCard == nullptr || destinationCard == nullptr)
    {
        return false;
    }

    if (!movingCard->isFaceUp() || !destinationCard->isFaceUp())
    {
        return false;
    }

    int movingRank = movingCard->getRank();
    int destinationRank = destinationCard->getRank();

    bool oppositeColor = movingCard->isRed() != destinationCard->isRed();

    // Using for debug turns out I actually like keeping the output though :)
    std::cout << "Comparing: " << movingCard->getRank() << " " << movingCard->getSuit()
              << " (" << movingCard->getColor() << ") to "
              << destinationCard->getRank() << " " << destinationCard->getSuit()
              << " (" << destinationCard->getColor() << ") --> "
              << (movingRank == destinationRank - 1 ? "✓ Rank" : "✗ Rank") << ", "
              << (oppositeColor ? "✓ Color" : "✗ Color") << "\n";

    return (movingRank == destinationRank - 1) && oppositeColor;
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

// Checking for win state all foundations will be topped with the King
bool Game::checkWinCondition() const
{
    for (int i = 0; i < 8; ++i)
    {
        if (foundations[i].isEmptyStack() || foundations[i].top()->getRank() != 13)
            return false;
    }
    return true;
}

