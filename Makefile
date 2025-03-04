CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lpthread -ltgui
SRC = $(wildcard *.cxx) $(wildcard Figures/*.cxx) $(wildcard UI/*.cxx)
OBJ = $(SRC:.cxx=.o)
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
