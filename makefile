
# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Target Executable
TARGET = forty_thieves

# Source Files
SRC = main.cpp Card.cpp Deck.cpp Game.cpp
# Object Files
OBJ = $(SRC:.cpp=.o)

# Default Rule
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJ)