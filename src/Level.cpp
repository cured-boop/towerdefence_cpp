#include "Level.h"

// Constructor
Level::Level(int levelNumber) : levelNumber(levelNumber) {
  // Initialization, perhaps allocate resources or prepare the level layout
}

// Destructor
Level::~Level() {
  // Free any dynamically allocated resources
  for (Tower *tower : towers) {
    delete tower;
  }
  for (Enemy *enemy : enemies) {
    delete enemy;
  }
}

// Spawn a new wave of enemies
void Level::spawnWave() {
  // Implement logic to spawn enemies, you can customize this based on
  // levelNumber or other criteria For example:
  for (int i = 0; i < levelNumber * 5; ++i) {
    Enemy *newEnemy = new Enemy(/* parameters */);
    enemies.push_back(newEnemy);
  }
}

// Adds a new tower to the level
void Level::addTower(Tower *tower) { towers.push_back(tower); }

// Removes a tower from the level
void Level::removeTower(int index) {
  if (index < 0 || index >= towers.size()) {
    // Handle index out of bounds
    return;
  }
  delete towers[index];
  towers.erase(towers.begin() + index);
}

// Updates the game state within the level
void Level::update() {
  // Update towers
  for (Tower *tower : towers) {
    tower->update();
  }

  // Update enemies
  for (Enemy *enemy : enemies) {
    enemy->move(); // Or whatever method moves the enemy
  }

  // Implement collision detection, projectile motion, etc.
  // For example, check if any tower's projectile hits any enemy
}

// Checks if the game is lost
bool Level::checkLoss() {
  // Implement the logic to check if the game is lost
  // For example, loop through enemies and see if any have reached the end of
  // the path
  for (Enemy *enemy : enemies) {
    if (enemy->hasReachedEnd()) {
      return true;
    }
  }
  return false;
}
