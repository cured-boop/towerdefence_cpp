#include "Sidebar.hpp"
#include "Constants.hpp"

Sidebar::Sidebar(float width, const sf::RenderWindow &window)
    : width(width), selectedTower(1) {
  background.setSize(sf::Vector2f(width, window.getSize().y));
  background.setFillColor(sf::Color(200, 200, 200));
  background.setPosition(windowWidth - width, 0);

  // Load tower textures and create sprites
  sf::Texture texture;
  if (texture.loadFromFile(
          "src/assets/cat.png")) { // Replace with actual file path
    towerTextures.push_back(texture);
    sf::Sprite sprite;
    sprite.setTexture(towerTextures.back());
    sprite.setPosition(windowWidth - width + 10,
                       10); // Adjust position as needed
    // Calculate scale factors
    float towerScaleX = static_cast<float>(tileSize) / texture.getSize().x;
    float towerScaleY = static_cast<float>(tileSize) / texture.getSize().y;
    sprite.setScale(towerScaleX, towerScaleY);
    towerSprites.push_back(sprite);
  }

  // Repeat the above block for each tower type
}

void Sidebar::draw(sf::RenderWindow &window) {
  window.draw(background);
  for (auto &sprite : towerSprites) {
    window.draw(sprite);
  }
}

float Sidebar::getWidth() { return width; }

int Sidebar::getSelectedTower() { return selectedTower; }

// Additional methods for handling user input, selecting towers, etc.
