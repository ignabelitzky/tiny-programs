CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++23 -O2 -march=native -g
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

TARGET := main

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFMLFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
