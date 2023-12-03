#include "Game.hpp"
#include <iostream>

// TODO: Replace these temporary initializations with file reads
const std::vector<std::vector<int>> layout = {
    {0, 0, 0, 3, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 0}, {0, 1, 1, 1, 1, 1, 0}, {0, 1, 0, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 0, 0}};

const std::vector<sf::Vector2i> path = {{1, 6}, {1, 5}, {1, 4}, {2, 4}, {3, 4},
                                        {4, 4}, {5, 4}, {5, 3}, {5, 2}, {4, 2},
                                        {3, 2}, {3, 1}, {3, 0}};

Enemy enemy = Enemy(path);

std::vector<Wave> waves = {Wave({enemy, enemy, enemy, enemy})};

Level _level = Level(layout, 1, waves, path);

Game::Game(sf::RenderWindow &win) : window(win), level(_level) {
  // TODO: Load the last state (including level, money, wave, towers and their
  // positions)
}

void Game::update() {
  sf::Time elapsed = gameClock.restart();
  float deltaTime = elapsed.asSeconds();
  handleEvents();
  updateEnemies(deltaTime);
  // updateTowers();
  checkCollisions();
  // Any other update logic (e.g., check game over, update state)
}

void Game::draw() {
  // Draw level
  level.draw(window);

  // Draw each enemy
  for (auto &enemy : level.enemies) {
    enemy.draw(window);
  }

  // Draw each tower
  /*for (auto &tower : towers) {
     tower.draw(window);
  }*/

  // Draw other game elements (e.g., UI, state)
}

void Game::handleEvents() {
  if (!level.hasEnemies())
    level.spawn = true;
  level.spawnNextWave();
}

void Game::updateEnemies(float deltaTime) {
  for (auto &enemy : level.enemies) {
    enemy.move(deltaTime);
    // Additional logic (e.g., remove enemy if it reaches the end)
  }
}

/*void Game::updateTowers() {
  for (auto &tower : towers) {
    // tower.update();
    // Additional logic (e.g., tower attacking enemies)
  }
}*/

void Game::checkCollisions() {
  // Check for collisions between tower projectiles and enemies
  // Implement collision logic
}
