CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++23 -O3
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

TARGET := main

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFMLFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

format:
	clang-format -style=Microsoft -i src/*.cpp include/*.hpp

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all format clean