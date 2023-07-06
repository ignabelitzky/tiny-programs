CXX := g++
CXXFLAGS := -O2 -march=native -std=c++23 -Wall -Werror -Wextra -pedantic
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

TARGET := main

SRC := main.cpp ray.cpp boundary.cpp particle.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ)
