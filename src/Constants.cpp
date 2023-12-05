#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

const int windowWidth = 900;
const int windowHeight = 700;
const int tileSize = 100;

const std::vector<int> towerPrices = {15, 30, 45};
const std::vector<int> towerRanges = {150, 300, 450};

void scaleSprite(sf::Sprite &sprite, const sf::Texture &texture) {

  // Calculate scale factors
  float scaleX = static_cast<float>(tileSize) / texture.getSize().x;
  float scaleY = static_cast<float>(tileSize) / texture.getSize().y;
  sprite.setScale(scaleX, scaleY);
}