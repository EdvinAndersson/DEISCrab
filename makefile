#all:
#	g++ -std=c++11 -o crab.out main.cpp motorhatlib/*.cpp

# Compiler and options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Source and output
SRC_MAIN = main.cpp
SRC_LIB = $(wildcard motorhatlib/*.cpp)
OBJ = $(SRC_MAIN:.cpp=.o) $(SRC_LIB:.cpp=.o)
TARGET = crab.out

# Default rule
all: $(TARGET)

# Link all object files into final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp → .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean