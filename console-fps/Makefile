CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++23 -O3 -march=native
LDFLAGS := -lncursesw

TARGET := main

SRC := src/main.cpp src/utils.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

format:
	clang-format -style=Microsoft -i src/*.cpp include/*.hpp

clean:
	rm -f $(OBJ) $(TARGET)
