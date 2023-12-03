
#include "Enemy.hpp"
#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Enemy::Enemy(const std::vector<sf::Vector2i> &path, double _speed, int _hp)
    : speed(_speed), hp(_hp), currentPathIndex(0) {
  position.x = tileSize * path.front().x;
  position.y = tileSize * path.front().y;

  // Load textures
  if (!enemyTexture.loadFromFile("src/assets/mouse.png")) {
    // Handle error
  }

  // Set textures to sprites
  enemySprite.setTexture(enemyTexture);

  // Calculate scale factors
  float enemyScaleX = static_cast<float>(tileSize) / enemyTexture.getSize().x;
  float enemyScaleY = static_cast<float>(tileSize) / enemyTexture.getSize().y;
  enemySprite.setScale(enemyScaleX, enemyScaleY);
}

void Enemy::setPosition(sf::Vector2f newPosition) { position = newPosition; }

void Enemy::draw(sf::RenderWindow &window) {
  enemySprite.setPosition(position.x, position.y);
  window.draw(enemySprite);
}

void Enemy::move(float deltaTime) {
  if (currentPathIndex >= path.size() - 1)
    return; // Check if the enemy has reached the end of the path
  // Next target position in world coordinates
  sf::Vector2f targetPosition(path[currentPathIndex + 1].x * tileSize,
                              path[currentPathIndex + 1].y * tileSize);
  // Calculate the direction vector
  sf::Vector2f direction = targetPosition - position;
  float length =
      std::sqrt(direction.x * direction.x + direction.y * direction.y);
  if (length != 0)
    direction /= length; // Normalize the direction vector
  // Move the enemy
  position.x += direction.x * speed * deltaTime;
  position.y += direction.y * speed * deltaTime;

  // Check if the enemy has reached the target position
  if (std::abs(position.x - targetPosition.x) < 0.1f &&
      std::abs(position.y - targetPosition.y) < 0.1f) {
    currentPathIndex++; // Move to the next point in the path
  }
}

void Enemy::setPath(std::vector<sf::Vector2i> _path) { path = _path; }

void Enemy::getHit(int dmg) { hp -= dmg; }
