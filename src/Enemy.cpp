
#include "Enemy.hpp"
#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Enemy::Enemy(const std::vector<sf::Vector2i> &path, double _speed, int _hp,
             int _money)
    : speed(_speed), hp(_hp), currentPathIndex(0), money(_money) {
  position.x = tileSize * path.front().x;
  position.y = tileSize * path.front().y;

  // Load textures
  if (!enemyTexture.loadFromFile("src/assets/mouse.png")) {
    // Handle error
  }

  // Set textures to sprites
  enemySprite.setTexture(enemyTexture);
  scaleSprite(enemySprite, enemyTexture);
}

void Enemy::setPosition(sf::Vector2f newPosition) { position = newPosition; }

void Enemy::die() { // Start death "animation" / delay
  deathClock.restart();
  dying = true;
}

void Enemy::draw(sf::RenderWindow &window) {
  enemySprite.setPosition(position.x, position.y);
  window.draw(enemySprite);
}

void Enemy::move(float deltaTime) {
  // Don't move if dead
  if (dying && deathClock.getElapsedTime().asSeconds() > 1) {
    isDead = true;
    return;
  }
  if (dying || currentPathIndex >= path.size() - 1)
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

void Enemy::getHit(int dmg) {
  std::cout << "HP: " << hp << " dmg: " << dmg << std::endl;
  hp -= dmg;
  std::cout << "HP now: " << hp << std::endl;
  if (hp <= 0)
    die();
}
