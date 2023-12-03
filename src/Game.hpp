#ifndef GAME_HPP
#define GAME_HPP

#include "Level.hpp" // Include your Level class header
//#include "State.hpp" // Include your State class header
#include "Sidebar.hpp"
#include <SFML/Graphics.hpp>

class Game {
public:
  Game(sf::RenderWindow &window);
  void update();
  void draw();
  void handleMouseClick(int x, int y);
  bool isValidPosition(int x, int y);

private:
  sf::RenderWindow &window;
  Level level; // Assuming Level class handles the game map
  // State state; // Assuming State class handles game state like money, wave
  // number, etc.
  std::vector<Enemy> enemies;
  // std::vector<Tower> towers;
  // Wave currentWave; // Current wave of enemies

  void handleEvents(const sf::Event &event); // Handle game-specific events
  void updateEnemies(float deltaTime);
  // void updateTowers();
  void checkCollisions();
  sf::Clock gameClock;
  Sidebar sidebar;
  int selectedTower;
  sf::Sprite enemySprite;
  sf::Texture enemyTexture;
};

#endif // GAME_HPP
