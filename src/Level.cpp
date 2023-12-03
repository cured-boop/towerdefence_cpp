#include "Level.hpp"
#include "Constants.hpp"
#include "Wave.hpp"

Level::Level(const std::vector<std::vector<int>> _layout, int _levelNum,
             std::vector<Wave> _waves, std::vector<sf::Vector2i> _path)
    : layout(_layout), levelNum(_levelNum), waves(_waves), path(_path),
      spawn(true) { // Level constructor

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

  // Calculate scale factors
  float grassScaleX = static_cast<float>(tileSize) / grassTexture.getSize().x;
  float grassScaleY = static_cast<float>(tileSize) / grassTexture.getSize().y;
  grassSprite.setScale(grassScaleX, grassScaleY);

  float roadScaleX = static_cast<float>(tileSize) / roadTexture.getSize().x;
  float roadScaleY = static_cast<float>(tileSize) / roadTexture.getSize().y;
  roadSprite.setScale(roadScaleX, roadScaleY);
} // Level constructor

const std::vector<std::vector<int>> &Level::getLayout() const { return layout; }

int Level::getLevelNum() { return levelNum; }
std::vector<Wave> Level::getWaves() { return waves; }
bool Level::hasEnemies() { return (enemies.size() != 0); }

void Level::draw(sf::RenderWindow &window) {
  for (int y = 0; y < layout.size(); y++) {
    for (int x = 0; x < layout[y].size(); x++) {
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

void Level::spawnNextWave() {
  if (!spawn) // Wave is in progress, do not spawn more
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