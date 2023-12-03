#ifndef GAME_HPP
#define GAME_HPP

#include "Enemy.hpp" // Include your Enemy class header
#include "Level.hpp" // Include your Level class header
//#include "State.hpp" // Include your State class header
//#include "Tower.hpp" // Include your Tower class header
#include "Wave.hpp" // Include your Wave class header
#include <SFML/Graphics.hpp>

class Game {
public:
  Game(sf::RenderWindow &window);
  void update();
  void draw();

private:
  sf::RenderWindow &window;
  Level level; // Assuming Level class handles the game map
  // State state; // Assuming State class handles game state like money, wave
  // number, etc.
  std::vector<Enemy> enemies;
  // std::vector<Tower> towers;
  // Wave currentWave; // Current wave of enemies

  void handleEvents(); // Handle game-specific events
  void updateEnemies(float deltaTime);
  // void updateTowers();
  void checkCollisions();
  sf::Clock gameClock;
};

#endif // GAME_HPP
