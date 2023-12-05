#include "Sidebar.hpp"
#include "Constants.hpp"
#include <iostream>

Sidebar::Sidebar(float width, const sf::RenderWindow &window)
    : width(width), selectedTower(1) {
  background.setSize(sf::Vector2f(width, window.getSize().y));
  background.setFillColor(sf::Color(200, 200, 200));
  background.setPosition(windowWidth - width, 0);

  // Load tower textures and create sprites
  sf::Texture texture;
  if (texture.loadFromFile("src/assets/cat0.png")) {
    towerTextures.push_back(texture);
    sf::Sprite sprite;
    sprite.setTexture(towerTextures.back());
    sprite.setPosition(windowWidth - width / 2 - tileSize / 2, 10);
    scaleSprite(sprite, texture);
    towerSprites.push_back(sprite);
  }
  // Repeat the above block for each tower type

  // Load font
  if (!font.loadFromFile("src/assets/arial.ttf")) {
    // Handle error
  }

  for (size_t i = 0; i < towerSprites.size(); ++i) {
    sf::Text priceText;
    priceText.setFont(font);
    priceText.setString("Price: " + std::to_string(towerPrices[i]));
    priceText.setCharacterSize(25);         // Set character size
    priceText.setFillColor(sf::Color::Red); // Set text color

    // Position the text below the corresponding tower sprite
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
  size_t index = 0;
  for (const auto &sprite : towerSprites) {
    if (sprite.getGlobalBounds().contains(position)) {
      // Check if the player has enough money for this tower
      if (index < towerPrices.size() && money >= towerPrices[index]) {
        return index; // Return the tower index (assuming it starts from 1)
      } else {
        return -1; // Not enough money or price not defined
      }
    }
    ++index;
  }
  return -1; // No tower selected
}