#include "Level.hpp"
#include "Constants.hpp"
#include "Wave.hpp"
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

Level::Level() {
  // Load textures
  if (!grassTexture.loadFromFile("src/assets/grass.png")) {
  }
  if (!roadTexture.loadFromFile("src/assets/road.png")) {
  }
  if (!rock0Texture.loadFromFile("src/assets/rock0.png")) {
  }
  if (!rock1Texture.loadFromFile("src/assets/rock1.png")) {
  }
  if (!rock2Texture.loadFromFile("src/assets/rock2.png")) {
  }
  if (!rock3Texture.loadFromFile("src/assets/rock3.png")) {
  }

  // Set textures to sprites
  grassSprite.setTexture(grassTexture);
  roadSprite.setTexture(roadTexture);
  rock0Sprite.setTexture(rock0Texture);
  rock1Sprite.setTexture(rock1Texture);
  rock2Sprite.setTexture(rock2Texture);
  rock3Sprite.setTexture(rock3Texture);
  scaleSprite(grassSprite);
  scaleSprite(roadSprite);
  scaleSprite(rock0Sprite);
  scaleSprite(rock1Sprite);
  scaleSprite(rock2Sprite);
  scaleSprite(rock3Sprite);
} // Level constructor

const std::vector<std::vector<int>> &Level::getLayout() const { return layout; }

std::vector<Wave> Level::getWaves() { return waves; }

bool Level::hasEnemies() { return (enemies.size() != 0); }

void Level::draw(sf::RenderWindow &window) {
  for (size_t y = 0; y < layout.size(); y++) {
    for (size_t x = 0; x < layout[y].size(); x++) {
      if (layout[y][x] == 0) {
        grassSprite.setPosition(x * tileSize, y * tileSize);
        window.draw(grassSprite);
      } else if (layout[y][x] == 1) {
        roadSprite.setPosition(x * tileSize, y * tileSize);
        window.draw(roadSprite);
      } else if (layout[y][x] == 2) {
        grassSprite.setPosition(x * tileSize, y * tileSize);
        window.draw(grassSprite);
        rock0Sprite.setPosition(x * tileSize, y * tileSize);
        window.draw(rock0Sprite);
      }
    }
  }
}

void Level::initialize(std::vector<std::vector<int>> _layout,
                       std::vector<sf::Vector2i> _path,
                       std::vector<Wave> _waves,
                       std::vector<Tower> purchasedTowers) {
  layout = _layout;
  path = _path;
  waves = _waves;
  towers = purchasedTowers;
  enemies.clear();
}

sf::Vector2i Level::calculateTile(float x, float y) {
  int gridSize = layout.front().size();
  // Assuming tileSize is the size of each tile in pixels
  int tileX = x / tileSize;
  int tileY = y / tileSize;

  // Make sure the calculated tile indices are within the bounds of the grid
  tileX = std::max(0, std::min(tileX, gridSize));
  tileY = std::max(0, std::min(tileY, gridSize));

  return sf::Vector2i(tileX, tileY);
}

bool Level::isEmpty(sf::Vector2i tile) {
  // First checks if 'tile' is not on road, then:
  // Checks all Towers in the vector<Tower> towers for their tile and returns
  // true if no towers are occupying 'tile'
  if (layout[tile.y][tile.x] != 0)
    return false;
  for (auto tower : towers) {
    sf::Vector2i towerTile = calculateTile(tower.position.x, tower.position.y);
    if (tile == towerTile)
      return false;
  }

  return true;
}

void Level::spawnNextWave() {
  if (waves.empty())
    return;
  // Erase the current empty wave from the wave vector
  std::cout << "Erasing empty wave" << std::endl;
  waves.erase(waves.begin()); // Remove the wave if all enemies are spawned
}

void Level::update(State &state) {
  if (waves.empty()) // Do not spawn if all waves have been spawned
    return;

  if (waves.front().getEnemies().empty() && enemies.empty()) {
    state.nextWave();
    spawnNextWave();
  }

  if (spawnClock.getElapsedTime().asSeconds() >= 3.0f) {
    // If there are still enemies remaining in the wave
    if (waves.front().getEnemies().size() != 0) {
      Enemy enemy = waves.front().getNextEnemy();
      enemy.initialize(path);
      std::cout << "Spawned one enemy at " << enemy.position.x << ", "
                << enemy.position.y << std::endl;
      enemies.push_back(enemy); // Add the enemy to the active enemies list
      spawnClock.restart();     // Restart the clock for the next enemy
    }
  }
}