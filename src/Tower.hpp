#ifndef TOWER_HPP
#define TOWER_HPP

#include "Pos.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include <vector>

class noTarget; // Forward declaration to break circular dependency

class Tower {
public:
    int dmg;
    int range;
    int cost;
    std::string Type;
    Pos pos;
    Game* game;

    Tower(int dmg, int range, int cost, std::string Type, Pos pos, Game* game);

    std::vector<Enemy> withinRange(std::vector<Enemy>& enemies);

    void attack(int time);

private:
    bool cooldown(int time);
};

class mainInfo {
public:
    int dmg;
    int range;
    int cost;

    mainInfo(int dmg, int range, int cost);
};

class towersToSaveState {
public:
    Game* game;
    std::map<int, mainInfo> Alltowers;

    towersToSaveState(Game* game, std::vector<Json::Value> JSONtower);

    std::optional<Tower> wrap(int Type, Pos pos = Pos(0, 0));
};

#endif // TOWER_HPP