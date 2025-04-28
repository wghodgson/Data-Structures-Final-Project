README - Forty Thieves Solitaire

Overview
This project implements a console-based version of the solitaire card game "Forty Thieves" using C++. 
The program follows object-oriented programming principles using modularity and good memory management coding practices. 

How to Run
1. Compile all .cpp files together with your preferred C++ compiler (e.g., g++, clang++).
   - Example: 
     g++ main.cpp card.cpp deck.cpp game.cpp -o forty_thieves
2. Run whatever you name it, forty_thieves for example:
   ./forty_thieves
3. Use the menu options to draw cards, move cards between tableau columns, move cards to foundations, view the current board, restart, or exit the game.

Project Structure
    - card.h & card.cpp: Represents individual playing cards with rank, suit, color, and face-up status.
    - deck.h & deck.cpp: Manages a full double-deck of shuffled cards.
    - game.h & game.cpp: Manages the overall game state, including tableau, foundations, waste pile, and the deck.
    - main.cpp: Provides a text-based menu system for player interaction.

Special Notes
    - ASCII art is used to simulate cards and the game board layout.
    - User input is fully validated.
    - Memory management is carefully handled to avoid leaks.
    - Data structures used (stack, queue, linked list) are adapted from the ones we did in class.

Hope you have fun playing Forty Thieves!
