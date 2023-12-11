#include "Sidebar.hpp"
#include "Constants.hpp"
#include <iostream>

Sidebar::Sidebar(float width, const sf::RenderWindow &window)
    : width(width),
      selectedTower(-1) { // Initialize with -1 (no tower selected)
  // Set up the background
  background.setSize(sf::Vector2f(width, window.getSize().y));
  background.setFillColor(sf::Color(200, 200, 200));
  background.setPosition(windowWidth - width, 0);

  // Load tower textures and create sprites for each tower type
  if (textureCat0.loadFromFile("src/assets/cat0.png")) {
    spriteCat0.setTexture(textureCat0);
    spriteCat0.setPosition(
        windowWidth - width / 2,
        tileSize * (1 + 0 * 2)); // Adjust vertical position for each tower
    scaleSprite(spriteCat0);
    centerSprite(sprite);
    towerSprites.push_back(sprite);
  }

  // Load font for prices
  if (!font.loadFromFile("src/assets/fredoka.ttf")) {
    // Handle error
  }

  // Create price texts for each tower
  for (size_t i = 0; i < towerSprites.size(); ++i) {
    sf::Text priceText;
    priceText.setFont(font);
    priceText.setString("Price: " + std::to_string(towerPrices[i]));
    priceText.setCharacterSize(30);
    priceText.setFillColor(sf::Color::Red);

    // Position text below each tower sprite
    sf::FloatRect spriteBounds = towerSprites[i].getGlobalBounds();
    priceText.setPosition(spriteBounds.left,
                          spriteBounds.top + spriteBounds.height + 10);
    towerPricesTexts.push_back(priceText);
  }
}

void Sidebar::draw(sf::RenderWindow &window) {
  window.draw(background);
  for (size_t i = 0; i < towerSprites.size(); ++i) {
    window.draw(towerSprites[i]);
    if (i < towerPricesTexts.size()) {
      window.draw(towerPricesTexts[i]);
    }
  }
}

float Sidebar::getWidth() { return width; }

int Sidebar::selectTower(int money, sf::Vector2f position) {
  for (size_t index = 0; index < towerSprites.size(); ++index) {
    if (towerSprites[index].getGlobalBounds().contains(position)) {
      // Check if the player has enough money for this tower
      if (index < towerPrices.size() && money >= towerPrices[index]) {
        return index; // Return the tower index
      } else {
        return -1; // Not enough money or price not defined
      }
    }
  }
  return -1; // No tower selected
}
