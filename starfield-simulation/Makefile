CXX := g++
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

TARGET := starfield

SRC := starfield.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(SFML_LIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJ)
