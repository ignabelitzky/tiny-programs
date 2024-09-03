CXX := g++
CXXFLAGS := -std=c++11 -Wall -Werror -Wextra -pedantic -march=native -O3 -ffast-math

SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

TARGET := main

SRC := src/main.cpp src/utils.cpp src/menu.cpp src/circle.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

format:
	clang-format -style=Microsoft -i src/*.cpp include/*.hpp

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean format
