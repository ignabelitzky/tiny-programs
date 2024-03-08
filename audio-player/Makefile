CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -pedantic -O3 -march=native -Wno-stringop-overflow
LDFLAGS := -ldl -lpthread -lm -lncurses

.PHONY: all clean

TARGET := main

SRC := src/main.cpp src/audio.cpp src/menu.cpp src/message_box.cpp src/helper.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ)