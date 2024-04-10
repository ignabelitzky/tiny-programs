CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++17 -O3 -march=native
LDFLAGS := -lm
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

TARGET := main
SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

.PHONY: all format clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(SFMLFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

format:
	clang-format -style=Microsoft -i src/*.cpp include/*.hpp

clean:
	rm -rf $(TARGET) $(OBJS)