#ifndef GAME_HPP
#define GAME_HPP

#include "Level.hpp" // Include your Level class header
#include "Sidebar.hpp"
#include "State.hpp" // Include your State class header
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
  void load(int level);
  void handleEvents(const sf::Event &event); // Handle game-specific events
  void updateEnemies(float deltaTime);
  void updateTowers();
  void drawGameLossScreen();
  sf::Clock gameClock;
  sf::Texture cursorTexture;
  sf::Sprite cursorSprite;
  sf::CircleShape rangeIndicator;
  sf::Font font;
  Sidebar sidebar;
  int selectedTower;
  std::vector<Tower> availableTowers;
  State state;
  Level level;
  bool isLost;
  int levelNum;

  //
  //
  // For game loss screen:
  sf::RectangleShape exitButton;
  sf::RectangleShape restartButton;
  sf::Text exitButtonText;
  sf::Text restartButtonText;

  void createLossScreenButtons();
  bool isOnButton(const sf::RectangleShape &button,
                  const sf::Vector2f &mousePos);
};

#endif // GAME_HPP
