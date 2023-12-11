#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

const int windowWidth = 900;
const int windowHeight = 700;
const int menuHeight = 700;
const int tileSize = windowHeight / 7;
const int tileSizeOffset = tileSize * 1.5;

const std::vector<int> towerPrices = {15, 4, 20};
const std::vector<int> towerRanges = {150, 230, 300};

const std::vector<int> enemyHPs = {30, 10, 45};
const std::vector<int> enemySpeeds = {70, 150, 40};
const std::vector<int> enemyMoneys = {5, 7, 10};

void scaleSprite(sf::Sprite &sprite) {
  const sf::Texture *texture = sprite.getTexture();
  // Calculate scale factors
  // Scale using the width
  float scale = static_cast<float>(tileSize) / texture->getSize().x;
  // Scale using the height
  // float scaleY = static_cast<float>(tileSize) / texture.getSize().y;
  sprite.setScale(scale, scale);
}

void centerSprite(sf::Sprite &sprite) {
  const sf::Texture *texture = sprite.getTexture();
  sprite.setOrigin((sf::Vector2f)texture->getSize() / 2.f);
}

sf::Vector2f tileToPosition(int tileX, int tileY) {
  // Assuming tileSize is the size of each tile in pixels
  float x = tileX * tileSize + tileSize / 2;
  float y = tileY * tileSize + tileSize / 2;

  return sf::Vector2f(x, y);
}

sf::Vector2f tileToPosition(sf::Vector2i v) {
  int tileX = v.x;
  int tileY = v.y;
  // Assuming tileSize is the size of each tile in pixels
  float x = tileX * tileSize + tileSize / 2;
  float y = tileY * tileSize + tileSize / 2;

  return sf::Vector2f(x, y);
}