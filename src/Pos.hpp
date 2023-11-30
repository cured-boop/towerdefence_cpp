//Reference in Game. Needs to be implemented. Represents a position in the game grid. 
#ifndef POS_HPP
#define POS_HPP
#include <iostream>

class Pos { //position of units in the game
public:
    int x, y;
    Pos(int firstx, int firsty) : x(firstx), y(firsty) {}

    void addx(int amount) { x += amount; }

    void addy(int amount) { y += amount; }
    std::string toString() { return "(" + std::to_string(x) + "," + std::to_string(y) + ")"; }
};
class PosD { //position in double
public:
    double x, y;

    PosD(double firstx, double firsty) : x(firstx), y(firsty) {}

    void addx(double amount) { x += amount; }
    void addy(double amount) { y += amount; }

    std::string toString() { return "(" + std::to_string(x) + "," + std::to_string(y) + ")"; }
};

#endif