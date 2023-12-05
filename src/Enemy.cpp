
#include "Enemy.hpp"
#include "Constants.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Enemy::Enemy(int _type) : type(_type), speedModifier(1) {

  std::string texturePath = "src/assets/mouse" + std::to_string(type) + ".png";
  if (!enemyTexture.loadFromFile(texturePath)) {
    // Handle error (e.g., texture file not found)
  }

  // Set textures to sprites
  enemySprite.setTexture(enemyTexture);
  scaleSprite(enemySprite);
  centerSprite(enemySprite);
}

void Enemy::initialize(std::vector<sf::Vector2i> path) {
  setPath(path);
  position = tileToPosition(path.front());
  speed = enemySpeeds[type];
  hp = enemyHPs[type];
  money = enemyMoneys[type];
}

void Enemy::slow() {
  slowClock.restart();
  speedModifier = 0.5;
}

void Enemy::die() { // Start death "animation" / delay
  deathClock.restart();
  dying = true;
}

void Enemy::draw(sf::RenderWindow &window) {
  enemySprite.setPosition(position.x, position.y);
  window.draw(enemySprite);
}

void Enemy::move(float deltaTime) {

  // If enemy is slowed
  if (slowClock.getElapsedTime().asSeconds() > 3)
    speedModifier = 1;

  // Don't move if dead
  if (dying && deathClock.getElapsedTime().asSeconds() > 1) {
    isDead = true;
    return;
  }

  // Don't move if dead
  if (dying)
    return;

  // Don't move if finished the path
  if (currentPathIndex >= path.size() - 1) {
    finished = true;
    return;
  }

  // Next target position in world coordinates
  sf::Vector2f targetPosition = tileToPosition(path[currentPathIndex + 1]);

  sf::Vector2f direction = targetPosition - position;
  float distanceToNextTile =
      std::sqrt(direction.x * direction.x + direction.y * direction.y);

  // Rotate the enemy to face the direction of movement
  float angle = std::atan2(direction.y, direction.x) * 180 / M_PI;

  // Set the rotation of the sprite
  enemySprite.setRotation(angle + 90);

  // Check if we will overstep the target in this move
  float stepSize = speed * speedModifier * deltaTime;
  if (stepSize > distanceToNextTile) {
    position = targetPosition; // Move directly to the target
    currentPathIndex++;        // Move to the next point in the path
  } else {
    // Normalize the direction vector
    direction /= distanceToNextTile;
    // Move the enemy
    position.x += direction.x * stepSize;
    position.y += direction.y * stepSize;
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
