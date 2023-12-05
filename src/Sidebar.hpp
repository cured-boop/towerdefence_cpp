#ifndef SIDEBAR_HPP
#define SIDEBAR_HPP

#include "Tower.hpp" // Include your Tower class
#include <SFML/Graphics.hpp>

class Sidebar {
public:
  Sidebar(float width, const sf::RenderWindow &window);
  void draw(sf::RenderWindow &window);
  int selectTower(int money,
                  sf::Vector2f position); // Returns the id of the tower or 0
  float getWidth();

private:
  float width;                            // Width of the sidebar
  sf::RectangleShape background;          // Background of the sidebar
  std::vector<sf::Texture> towerTextures; // Textures for the available towers
  std::vector<sf::Sprite> towerSprites;   // Sprites for the available towers
  int selectedTower;                      // Currently selected tower
  std::vector<sf::Text> towerPricesTexts; // Vector to store price texts
  sf::Font font;                          // Font for rendering text
};

#endif // SIDEBAR_HPP
