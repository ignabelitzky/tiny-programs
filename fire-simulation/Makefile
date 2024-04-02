CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++23 -O3 -march=native
OMPFLAGS := -fopenmp

TARGET := main

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -c -o $@ $<

format:
	clang-format -style=Microsoft -i src/*.cpp

clean:
	rm -f $(TARGET) $(OBJS)
