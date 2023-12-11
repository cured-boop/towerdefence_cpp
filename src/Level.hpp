#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "State.hpp"
#include "Tower.hpp"
#include "Wave.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm> // For std::find
#include <iostream>  // For testing, you can remove this in production code
#include <list>
#include <vector>

class Level {
public:
  Level();
  void initialize(std::vector<std::vector<int>> layout,
                  std::vector<sf::Vector2i> path, std::vector<Wave> waves,
                  std::vector<Tower> purchasedTowers);

  const std::vector<std::vector<int>> &getLayout() const;

  void draw(sf::RenderWindow &window);
  std::vector<Wave> getWaves();

  std::vector<sf::Vector2i> path;

  std::list<Enemy> enemies;
  std::vector<Tower> towers;

  bool hasEnemies();

  void spawnNextWave();

  sf::Vector2i calculateTile(float x, float y);

  bool isEmpty(sf::Vector2i tile);

  bool getLevelWon();

  void setLevelWon(bool state);

  void update(State &state);

  State state;

private:
  // Matrix representation of the level, where 0 = grass, 1 = road, 2 = start,
  // 3 = end
  std::vector<std::vector<int>> layout;

  // Textures for grass/roads/rocks
  sf::Texture grassTexture;
  sf::Texture roadTexture;
  sf::Texture rock0Texture;
  sf::Texture rock1Texture;
  sf::Texture rock2Texture;
  sf::Texture rock3Texture;
  sf::Sprite grassSprite;
  sf::Sprite roadSprite;
  sf::Sprite rock0Sprite;
  sf::Sprite rock1Sprite;
  sf::Sprite rock2Sprite;
  sf::Sprite rock3Sprite;

  const int tileSize = 100; // The size of each road/grass tile on screen
  std::vector<Wave> waves;
  int levelNum;
  bool levelWon = false;
  
  sf::Clock spawnClock;
};

#endif // LEVEL_HPP