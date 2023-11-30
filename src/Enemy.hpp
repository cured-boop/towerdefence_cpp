//reference in Game, needs to be implemented. Represents enemies.
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Pos.hpp"

class Enemy {
public:
    double speed;
    int fullhp;
    PosD pos;
    int hp;
    int toDirection;
    int onRoad;
    int toFinish;

    Enemy(double speed = 1.0, int fullhp = 100);

    void move(int x, int y);

    void getHit(int dmg);

    bool madeIt();
};


#endif