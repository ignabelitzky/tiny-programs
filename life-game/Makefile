CXX := g++
CXXFLAGS := -O2 -march=native -Wall -Werror -Wextra -pedantic -std=c++23
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
OMP_LIBS := -fopenmp

TARGET := life

SRC := main.cpp helper.cpp
OBJ := $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(OMP_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(SFML_LIBS) $(OMP_LIBS)

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: clean
