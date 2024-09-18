CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++23 -O3 -march=native -g
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
OMPFLAGS := -fopenmp

TARGET := main

SRC := src/main.cpp src/utils.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFMLFLAGS) $(OMPFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(SFMLFLAGS) $(OMPFLAGS)

format:
	clang-format -style=Microsoft -i src/*.cpp include/*.hpp

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean format
