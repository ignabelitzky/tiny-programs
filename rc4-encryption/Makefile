CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror -pedantic -O3

SRC := src/encrypt.cpp src/decrypt.cpp src/utils.cpp
OBJ := $(SRC:.cpp=.o)

all: encrypt decrypt

encrypt: src/encrypt.o src/utils.o
	$(CXX) $(CXXFLAGS) -o $@ $^

decrypt: src/decrypt.o src/utils.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) encrypt decrypt *_output.txt
