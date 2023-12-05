#ifndef GAME_HPP
#define GAME_HPP

#include "Level.hpp" // Include your Level class header
#include "Sidebar.hpp"
#include "State.hpp" // Include your State class header
#include <SFML/Graphics.hpp>

class Game {
public:
  Game(sf::RenderWindow &window, State state);
  void update();
  void draw();
  void handleMouseClick(int x, int y);
  bool isValidPosition(int x, int y);

private:
  sf::RenderWindow &window;

  void handleEvents(const sf::Event &event); // Handle game-specific events
  void updateEnemies(float deltaTime);
  void updateTowers();
  sf::Clock gameClock;
  sf::Texture cursorTexture;
  sf::Sprite cursorSprite;
  sf::CircleShape rangeIndicator;
  Sidebar sidebar;
  int selectedTower;
  State state;
  Level level;
};

#endif // GAME_HPP
