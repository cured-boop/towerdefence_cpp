# Variables for include and library directories
SFML_INCLUDE = libs/SFML/include
SFML_LIB = libs/SFML/lib

all: compile link

compile:
	g++ -I$(SFML_INCLUDE) -Isrc/include -c main.cpp

link:
	g++ main.o -o main -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system
