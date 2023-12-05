#include "Level.hpp"
#include "Constants.hpp"
#include "Wave.hpp"

Level::Level(const std::vector<std::vector<int>> _layout, int _levelNum,
             std::vector<Wave> _waves, std::vector<sf::Vector2i> _path)
    : path(_path), spawn(true), layout(_layout), waves(_waves),
      levelNum(_levelNum) { // Level constructor

  // Load textures
  if (!grassTexture.loadFromFile("src/assets/grass.png")) {
    // Handle error
  }
  if (!roadTexture.loadFromFile("src/assets/road.png")) {
    // Handle error
  }

  // Set textures to sprites
  grassSprite.setTexture(grassTexture);
  roadSprite.setTexture(roadTexture);
  scaleSprite(grassSprite, grassTexture);
  scaleSprite(roadSprite, roadTexture);
} // Level constructor

const std::vector<std::vector<int>> &Level::getLayout() const { return layout; }

int Level::getLevelNum() { return levelNum; }
std::vector<Wave> Level::getWaves() { return waves; }
bool Level::hasEnemies() { return (enemies.size() != 0); }

void Level::draw(sf::RenderWindow &window) {
  for (size_t y = 0; y < layout.size(); y++) {
    for (size_t x = 0; x < layout[y].size(); x++) {
      if (layout[y][x] == 0) {
        grassSprite.setPosition(x * tileSize, y * tileSize);
        window.draw(grassSprite);
      } else if (layout[y][x] == 1 || layout[y][x] == 2 || layout[y][x] == 3) {
        roadSprite.setPosition(x * tileSize, y * tileSize);
        window.draw(roadSprite);
      }
    }
  }
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
    std::cout << towerTile.x << " = " << tile.x << ", " << towerTile.y << " = "
              << tile.y << std::endl;
    if (tile == towerTile)
      return false;
  }

  return true;
}

void Level::spawnNextWave() {
  if (!spawn || waves.empty()) // Do not spawn more if wave in progress or empty
    return;

  if (spawnClock.getElapsedTime().asSeconds() >= 3.0f) {
    // If there are still enemies remaining in the wave
    std::cout << "Size of wave: " << waves.front().getEnemies().size()
              << std::endl;
    if (waves.front().getEnemies().size() != 0) {
      std::cout << "Spawned one enemy" << std::endl;
      Enemy enemy = waves.front().getNextEnemy();
      enemy.setPath(path);
      enemies.push_back(enemy); // Add the enemy to the active enemies list
      spawnClock.restart();     // Restart the clock for the next enemy
    } else {
      std::cout << "Ereasing empty wave" << std::endl;
      waves.erase(waves.begin()); // Remove the wave if all enemies are spawned
      spawn = false;              // Spawning complete
    }
  }
}