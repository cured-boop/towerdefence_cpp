#include "Game.hpp"

std::vector<std::vector<int>> layout = {
    {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 0}, {0, 1, 1, 1, 1, 1, 0}, {0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0}};

Game::Game(sf::RenderWindow &win)
    : window(win), level(Level(layout, 1000, 1000)) {
  // Initialize game components, like loading the level, initializing the state,
  // etc. level = ... state = ... currentWave = ...
}

void Game::update() {
  handleEvents();
  // updateEnemies();
  // updateTowers();
  checkCollisions();
  // Any other update logic (e.g., check game over, update state)
}

void Game::draw() {
  // Draw level
  level.draw(window);

  // Draw each enemy
  for (auto &enemy : enemies) {
    // enemy.draw(window);
  }

  // Draw each tower
  /*for (auto &tower : towers) {
     tower.draw(window);
  }*/

  // Draw other game elements (e.g., UI, state)
}

void Game::handleEvents() {
  // Handle specific game events here (e.g., spawning enemies, managing waves)
}

/*void Game::updateEnemies() {
  for (auto &enemy : enemies) {
    // enemy.update();
    // Additional logic (e.g., remove enemy if it reaches the end)
  }
}*/

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
