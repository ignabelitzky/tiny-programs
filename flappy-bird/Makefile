CXX := g++
CXXFLAGS := -O2 -march=native -Wall -Werror -Wextra -pedantic -std=c++23
SFML_LIBS := -lsfml-graphics -lsfml-system -lsfml-window

TARGET := flappy

SRC := main.cpp bird.cpp pipe.cpp
OBJ := $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f $(TARGET) $(OBJ)
