//Referenced in Game. Needs to be implemented. Represents a wave of enemies. 
#include <map>
#include <vector>
#include "Enemy.hpp"
class Wave {
public:
    int goldReward;
    int index;

    Wave(int goldReward, int index = 1);

    int number();

    std::vector<Enemy> enemies();

    void next();

    void load(int wave);

    int reward();

private:
    std::map<int, int> waves;
};