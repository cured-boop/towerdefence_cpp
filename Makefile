CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 $(shell pkg-config --cflags sfml-all)
LDFLAGS = $(shell pkg-config --libs sfml-all)

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean