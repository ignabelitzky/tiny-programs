CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -O3 -march=native
LDFLAGS := -ldl -lpthread -lm

.PHONY: all clean

TARGET := main

SRC := src/main.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ)