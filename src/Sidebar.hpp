#ifndef SIDEBAR_HPP
#define SIDEBAR_HPP

#include "Tower.hpp" // Include your Tower class
#include <SFML/Graphics.hpp>

class Sidebar {
public:
  Sidebar(float width, const sf::RenderWindow &window);
  void draw(sf::RenderWindow &window);
  int getSelectedTower(); // Returns the selected tower or nullptr if none
  float getWidth();

private:
  float width;                            // Width of the sidebar
  sf::RectangleShape background;          // Background of the sidebar
  std::vector<sf::Texture> towerTextures; // Textures for the available towers
  std::vector<sf::Sprite> towerSprites;   // Sprites for the available towers
  int selectedTower;                      // Currently selected tower
  // Additional UI elements, like buttons or icons
};

#endif // SIDEBAR_HPP
