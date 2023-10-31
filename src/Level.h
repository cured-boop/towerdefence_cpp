#ifndef LEVEL_H
#define LEVEL_H

#include "Enemy.h" // Assuming Enemy is already defined
#include "Tower.h" // Assuming Tower is already defined
#include <vector>

class Level {
public:
  Level(int levelNumber);
  ~Level();

  void spawnWave(); // Spawns a new wave of enemies
  // void addTower(Tower *tower); // Adds a new tower to the level
  void removeTower(int index); // Removes a tower from the level
  void update();               // Updates the game state within the level
  bool checkLoss();            // Checks if the game is lost

private:
  int levelNumber; // The current level number
  // std::vector<Tower *> towers;  // List of towers in the level
  // std::vector<Enemy *> enemies; // List of enemies in the level
};

#endif // LEVEL_H
