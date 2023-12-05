#include "Game.hpp"
#include "Constants.hpp"
#include <algorithm>
#include <iostream>

// TODO: Replace these temporary initializations with file reads
const std::vector<std::vector<int>> layout = {
    {0, 0, 0, 3, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 0}, {0, 1, 1, 1, 1, 1, 0}, {0, 1, 0, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 0, 0}};

const std::vector<sf::Vector2i> path = {
    {1, 7}, {1, 6}, {1, 5}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4},
    {5, 3}, {5, 2}, {4, 2}, {3, 2}, {3, 1}, {3, 0}, {3, -1}};

Enemy enemy = Enemy(path);

Enemy enemy2 = Enemy(path, 100.0, 20, 10);

Enemy enemy3 = Enemy(path, 150.0, 20, 10);

std::vector<Wave> waves = {Wave({enemy}), Wave({enemy, enemy2}),
                           Wave({enemy, enemy2, enemy})};

Level _level = Level(layout, 1, waves, path);

Tower tower = Tower(10, 150, 10, 2);

Game::Game(sf::RenderWindow &win, State _state)
    : window(win), sidebar(200, window), state(_state), level(_level) {
  // TODO: Load the last state (including level, money, wave, towers and their
  // positions)
}

void Game::update() {
  sf::Event event;
  while (window.pollEvent(event)) {
    handleEvents(event); // Pass each event to the handler
  }
  sf::Time elapsed = gameClock.restart();
  float deltaTime = elapsed.asSeconds();
  updateTowers();
  updateEnemies(deltaTime);
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
    tower.draw(window);
  }

  state.draw(window);

  if (selectedTower >= 0) {
    window.draw(rangeIndicator); // Draw the range indicator
    window.draw(cursorSprite);   // Draw the cursor sprite
  }
}

void Game::handleEvents(const sf::Event &event) {

  if (event.type == sf::Event::Closed) {
    window.close();
  }

  if (selectedTower >= 0) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    cursorSprite.setPosition(mousePosition.x - tileSize / 2,
                             mousePosition.y - tileSize / 2);
    rangeIndicator.setPosition(
        mousePosition.x, mousePosition.y); // Update range indicator position
  }

  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      handleMouseClick(event.mouseButton.x, event.mouseButton.y);
    }
  }

  // Other event handling...
}

void Game::updateEnemies(float deltaTime) {
  level.enemies.remove_if([this, deltaTime](Enemy &enemy) {
    if (enemy.hp <= 0) {
      state.addMoney(enemy.money);
      return true; // Remove the enemy and add its money to the player
    } else {
      enemy.move(deltaTime);
      return false; // Keep and move the enemy
    }
  });
}

void Game::updateTowers() {
  for (auto &tower : level.towers) {
    tower.attack(level.enemies);
  }
}

void Game::handleMouseClick(int x, int y) {
  // Check if the click is within the sidebar
  std::cout << "Checking if the click was within sidebar" << std::endl;
  if (x >= window.getSize().x - sidebar.getWidth()) {
    std::cout << "The click was within sidebar" << std::endl;
    // Handle sidebar interaction
    selectedTower = sidebar.selectTower(state.money(), sf::Vector2f(x, y));
    if (selectedTower >= 0) {
      std::string texturePath =
          "src/assets/cat" + std::to_string(selectedTower) + ".png";
      if (!cursorTexture.loadFromFile(texturePath)) {
        // Handle error (e.g., texture file not found)
      }
      cursorSprite.setTexture(cursorTexture);
      scaleSprite(cursorSprite, cursorTexture); // Scale it to the correct size

      // Initialize the range indicator
      rangeIndicator.setRadius(towerRanges[selectedTower]);
      rangeIndicator.setFillColor(
          sf::Color(255, 255, 255, 128)); // Half-transparent white
      rangeIndicator.setOrigin(
          rangeIndicator.getRadius(),
          rangeIndicator.getRadius()); // Set origin to the center of the circle
    }
  } else {
    // Handle map interaction
    // Check if a tower is selected and the click is on a valid position
    std::cout << "Checking if the click was on a valid position (and tower is "
                 "selected)"
              << std::endl;
    if (selectedTower >= 0 && isValidPosition(x, y)) {
      // Place the tower on the map
      std::cout << "Placing the tower" << std::endl;
      tower.setPosition(level.calculateTile(x, y));
      level.towers.push_back(tower);
      // Pay for the tower
      state.addMoney(-towerPrices[selectedTower]);
      // Reset selected tower
      selectedTower = -1;
    }
  }
}

bool Game::isValidPosition(int x, int y) {
  return level.isEmpty(level.calculateTile(x, y));
}