// Referenced in Game. Needs to be implemented. Represents a wave of enemies.
#ifndef WAVE_HPP
#define WAVE_HPP

#include "Enemy.hpp"
#include <vector>
class Wave {
public:
  Wave(std::vector<Enemy> enemylist);

  const std::vector<Enemy> getEnemies();

  Enemy getNextEnemy();

private:
  std::vector<Enemy> enemies;
};
#endif
