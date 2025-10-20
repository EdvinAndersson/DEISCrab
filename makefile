# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -I/usr/local/include -Wall -Wextra
LDFLAGS = -lpigpio -lpthread -L/usr/local/lib 

# Sources
SRC_MAIN = main.cpp encoders.cpp
SRC_LIB = $(wildcard motorhatlib/*.cpp) 
SRC = $(SRC_MAIN) $(SRC_LIB)

# Object files
OBJ = $(SRC:.cpp=.o)

# Target executable
TARGET = crab.out

# Default rule
all: $(TARGET)

# Link object files
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile .cpp → .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean