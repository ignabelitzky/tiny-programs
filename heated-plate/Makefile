CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Werror -pedantic -O3 -march=native
CXXLIBS := -lm

TARGET := main

SRC := src/main.cpp src/utils.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(CXXLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ)