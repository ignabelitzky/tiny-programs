CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror -pedantic -O3
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

TARGET := main

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFMLFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(SFMLFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean