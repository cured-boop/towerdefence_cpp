#include "Game.hpp"
#include "Constants.hpp"
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

Game::Game(sf::RenderWindow &win)
    : window(win), level(_level), sidebar(200, window) {
  // TODO: Load the last state (including level, money, wave, towers and their
  // positions)

  // Load textures
  if (!enemyTexture.loadFromFile("src/assets/cat.png")) {
    // Handle error
  }

  // Set textures to sprites
  enemySprite.setTexture(enemyTexture);

  // Calculate scale factors
  float enemyScaleX = static_cast<float>(tileSize) / enemyTexture.getSize().x;
  float enemyScaleY = static_cast<float>(tileSize) / enemyTexture.getSize().y;
  enemySprite.setScale(enemyScaleX, enemyScaleY);
}

void Game::update() {
  sf::Event event;
  while (window.pollEvent(event)) {
    handleEvents(event); // Pass each event to the handler
  }
  sf::Time elapsed = gameClock.restart();
  float deltaTime = elapsed.asSeconds();
  updateEnemies(deltaTime);
  // updateTowers();
  checkCollisions();
  // Any other update logic (e.g., check game over, update state)

  if (!level.hasEnemies()) // Spawns new wave
    level.spawn = true;
  level.spawnNextWave();
}

void Game::draw() {
  // Draw level
  level.draw(window);
  sidebar.draw(window);
  // Draw each enemy
  for (auto &enemy : level.enemies) {
    enemy.draw(window);
  }

  // Draw each tower
  for (auto &tower : level.towers) {
    enemySprite.setPosition(tower.position.x - tileSize / 2,
                            tower.position.y - tileSize / 2);
    window.draw(enemySprite);
  }

  // Draw other game elements (e.g., UI, state)
}

void Game::handleEvents(const sf::Event &event) {

  if (event.type == sf::Event::Closed) {
    window.close();
  }

  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      handleMouseClick(event.mouseButton.x, event.mouseButton.y);
    }
  }

  // Other event handling...
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

void Game::handleMouseClick(int x, int y) {
  // Check if the click is within the sidebar
  std::cout << "Checking if the click was within sidebar" << std::endl;
  if (x >= window.getSize().x - sidebar.getWidth()) {
    std::cout << "The click was indeed within sidebar" << std::endl;
    // Handle sidebar interaction
    selectedTower = sidebar.getSelectedTower();
    if (selectedTower) {
      // Do something with the selected tower
      // e.g., prepare to place it on the map
    }
  } else {
    // Handle map interaction
    // Check if a tower is selected and the click is on a valid position
    std::cout << "Checking if the click was on a valid position (and tower is "
                 "selected)"
              << std::endl;
    if (selectedTower && isValidPosition(x, y)) {
      // Place the tower on the map
      std::cout << "Placing the tower" << std::endl;
      level.towers.push_back(Tower(10, 10, 10, sf::Vector2f(x, y)));
      // Reset selected tower
      selectedTower = 0;
    }
  }
}

bool Game::isValidPosition(int x, int y) {
  // TODO: Implement logic to check if the position is valid for placing a tower
  // E.g., not on a path, not occupied by another tower
  return true; // Placeholder
}