/*
#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>
#include <tuple>
#include <map>




class Game {
private:
    SaverLoader reader;

    // Declare other member variables as needed

public:
    Game();

    std::tuple<int, int, int, int, std::vector<Json::Value>, std::vector<std::vector<int>>> loadConfig();

    bool loadGame();

    void onTick();

    void save();

    void start();

    void engage();

    Direction toDirection(Enemy enemy);

    bool lastTile(Enemy enemy);

    void moveEnemies();

    void timeToAttack(int time);

    void enemyDoesNotDie(int index);

    void enemyDies();

    void onClick(Component src, Point cursor);

    void message(std::string msg);

    void removeMessage();

    bool won();

    bool lost();

    bool levelOver();

    void afterLevel();

    void towerWasChosen(int Type);

    Tower* chooseTower(Point cursor);

    void placeable(Point cursor, Tower* tower);

    void place(Tower* tower);
};

enum Direction {
    none,
    left,
    right,
    up,
    down
};

#endif // GAME_HPP

*/