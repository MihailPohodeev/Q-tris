CXX = g++
CXXFLAGS = -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lpthread
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
