#include "Wave.hpp"
#include <iostream>

Wave::Wave(std::vector<Enemy> enemyList) : enemies(enemyList) {}

const std::vector<Enemy> Wave::getEnemies() { return enemies; }

Enemy Wave::getNextEnemy() {
  Enemy enemy = enemies.front();
  enemies.erase(enemies.begin());
  return enemy;
}