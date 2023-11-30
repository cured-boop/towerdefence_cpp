//Referenced in Game. Needs to be implemented. Represents the current game state. class Tower; // Forward declaration
#ifndef OVERALL_HPP
#define OVERALL_HPP

#include "Tower.hpp"



class State {
public:
    State(int hp, int gold);
    void damage();
    void bought(const Tower& tower);
    bool buyable(const Tower& tower) const;
    bool isOver() const;
    void money(int amount);
    void loadStatus(const Json::Value& json);

private:
    int hp;
    int gold;
};

#endif // OVERALL_HPP