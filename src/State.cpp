/*#include "State.hpp"
#include "Tower.hpp" // Include necessary header file for Tower class

State::State(int hp, int gold) : hp(hp), gold(gold) {}

void State::damage() { hp -= 1; }

void State::bought(const Tower &tower) { gold -= tower.cost; }

bool State::buyable(const Tower &tower) const { return gold >= tower.cost; }

bool State::isOver() const { return hp > 0; }

void State::money(int amount) { gold += amount; }
/*
void State::loadStatus(const Json::Value& json) {
    gold = json["gold"].asInt();
    hp = json["hp"].asInt();
}*/