CXX = g++
CXXFLAGS = -std=c++11 -Wall
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = mandelbrot

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

format:
	clang-format -style=Microsoft -i *.cpp *.h

clean:
	rm -f $(OBJS) $(TARGET)

