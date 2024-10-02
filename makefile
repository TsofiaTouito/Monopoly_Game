# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -I/usr/include/SFML

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS = \
    Square.hpp \
    StreetSquare.hpp \
    UtilitySquare.hpp \
    SpecialSquare.hpp \
    Board.hpp \
    Player.hpp \
    GameManager.hpp \
    GUI_Manager.hpp \
    MonopolyGame.cpp \
    Board.cpp \
    Player.cpp \
    StreetSquare.cpp \
    SpecialSquare.cpp \
    GUI_Manager.cpp \
    GameManager.cpp

# Object files corresponding to the source files
OBJS = $(SRCS:.cpp=.o)

# Output executable name
TARGET = MonopolyGame

# Build target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(SFML_LIBS)

# Compile each source file in the specified order
# Square.hpp and its derived classes
Square.hpp: 
	@:

StreetSquare.hpp: Square.hpp
	@:

UtilitySquare.hpp: Square.hpp
	@:

SpecialSquare.hpp: Square.hpp
	@:

Board.hpp: 
	@:

Player.hpp: 
	@:

GameManager.hpp: 
	@:

GUI_Manager.hpp: 
	@:

# Individual object file rules
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)


