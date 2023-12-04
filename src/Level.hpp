#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Tower.hpp"
#include "Wave.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm> // For std::find
#include <iostream>  // For testing, you can remove this in production code
#include <list>
#include <vector>

class Level {
public:
  Level(const std::vector<std::vector<int>> layout, int levelNum,
        std::vector<Wave> waves, std::vector<sf::Vector2i> path);

  const std::vector<std::vector<int>> &getLayout() const;

  void draw(sf::RenderWindow &window);
  std::vector<Wave> getWaves();
  int getLevelNum();

  std::list<Enemy> enemies;
  std::vector<Tower> towers;

  bool hasEnemies();

  void spawnNextWave();

  std::vector<sf::Vector2i> path;

  bool spawn;

  sf::Vector2i calculateTile(float x, float y);

  bool isEmpty(sf::Vector2i tile);

private:
  // Matrix representation of the level, where 0 = grass, 1 = road, 2 = start,
  // 3 = end
  std::vector<std::vector<int>> layout;

  // Textures for grass/roads
  sf::Texture grassTexture;
  sf::Texture roadTexture;
  sf::Sprite grassSprite;
  sf::Sprite roadSprite;

  const int tileSize = 100; // The size of each road/grass tile on screen
  std::vector<Wave> waves;
  int levelNum;

  sf::Clock spawnClock;
};

#endif // LEVEL_HPP