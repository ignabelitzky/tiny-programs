CXX := g++
CXXFLAGS := -std=c++23 -march=native -O2
NCURSES_LIBS := -lncurses
OPENCV_LIBS := `pkg-config --cflags --libs opencv`

TARGET := cam-player

SRC := main.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(NCURSES_LIBS) $(OPENCV_LIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(OPENCV_LIBS)

clean:
	rm -f $(TARGET) $(OBJ)