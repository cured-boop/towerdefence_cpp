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
  State state;
private:
  sf::RenderWindow &window;
  void load(int level);
  void handleEvents(const sf::Event &event); // Handle game-specific events
  void updateEnemies(float deltaTime);
  void updateTowers();
  void drawGameLossScreen();
  void drawGameWinScreen();
  sf::Clock gameClock;
  sf::Texture cursorTexture;
  sf::Sprite cursorSprite;
  sf::CircleShape rangeIndicator;
  sf::Font font;
  Sidebar sidebar;
  int selectedTower;
  std::vector<Tower> availableTowers;
  Level level;
  bool isLost;
  int levelNumber = 0;

  // Tower Sprites:
  sf::Texture textureCat0, textureCat1, textureCat2;
  sf::Sprite spriteCat0, spriteCat1, spriteCat2;
  std::vector<sf::Sprite> towerSprites;

  //
  //
  // For game loss screen:
  sf::RectangleShape exitButton;
  sf::RectangleShape nextButton;
  sf::RectangleShape restartButton;
  sf::Text exitButtonText;
  sf::Text nextButtonText;
  sf::Text restartButtonText;

  void createLossScreenButtons();
  void createWinScreenButtons();
  bool isOnButton(const sf::RectangleShape &button,
                  const sf::Vector2f &mousePos);
};

#endif // GAME_HPP
