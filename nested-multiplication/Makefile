CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror -pedantic -O3

all: main

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f main main.o

.PHONY: all clean