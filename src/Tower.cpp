#include "Tower.hpp"
#include "Constants.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

Tower::Tower(int _dmg, int _range, int _cost, int _delay, int _type)
    : dmg(_dmg), range(_range), cost(_cost), delay(_delay), type(_type) {

  // Load textures
  std::string texturePath = "src/assets/cat" + std::to_string(_type) + ".png";
  if (!towerTexture.loadFromFile(texturePath)) {
    // Handle error (e.g., texture file not found)
  }

  if (type != 1) {
    if (!attackTexture.loadFromFile("src/assets/claw.png")) {
      // Handle error
    }
  } else if (!attackTexture.loadFromFile("src/assets/hairball.png")) {
    // Handle error
  }

  // Set textures to sprites
  towerSprite.setTexture(towerTexture);
  attackSprite.setTexture(attackTexture);

  scaleSprite(towerSprite);
  scaleSprite(attackSprite);
  centerSprite(towerSprite);
  centerSprite(attackSprite);
}

void Tower::setPosition(sf::Vector2i newPosition) {
  position = tileToPosition(newPosition);
}

void Tower::draw(sf::RenderWindow &window) {
  towerSprite.setPosition(position.x, position.y);
  window.draw(towerSprite);

  if (type == 0) {
    if (cooldownClock.getElapsedTime().asSeconds() < delay / 2) {
      if (target && !target->isDead) {
        attackSprite.setPosition(target->position);
        window.draw(attackSprite);
      }
    } else
      target = nullptr;
  }

  if (type == 1 && attacking) {
    // Animate attackSprite for Type 1 tower
    if (target)
      attackTargetPosition = target->position;
    sf::Vector2f direction = attackTargetPosition - attackSprite.getPosition();
    float distance =
        std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 10.0f) {  // Arbitrary small distance for collision
      direction /= distance; // Normalize
      attackSprite.move(direction * attackSpeed); // Move attackSprite
      window.draw(attackSprite);
    } else {
      attacking = false; // Stop animation when it reaches the target
    }
  }
}

std::vector<std::list<Enemy>::iterator>
Tower::withinRange(std::list<Enemy> &enemies) {
  std::vector<std::list<Enemy>::iterator> result;

  // Find enemies within range
  for (auto it = enemies.begin(); it != enemies.end(); ++it) {
    double distance = std::sqrt(std::pow(it->position.x - position.x, 2) +
                                std::pow(it->position.y - position.y, 2));
    if (distance < range && it->hp > 0) {
      result.push_back(it);
    }
  }

  // Sort the enemies by their distance to the last path tile
  std::sort(
      result.begin(), result.end(),
      [](const std::list<Enemy>::iterator &a,
         const std::list<Enemy>::iterator &b) {
        if (a->currentPathIndex != b->currentPathIndex) {
          return a->currentPathIndex >
                 b->currentPathIndex; // Descending order of currentPathIndex
        }
        return a->distanceToNextTile >
               b->distanceToNextTile; // Descending order of distanceToNextTile
      });

  return result;
}

void Tower::attack(std::list<Enemy> &enemies) {
  if (cooldownClock.getElapsedTime().asSeconds() >= delay) {
    auto enemiesInRange = withinRange(enemies);
    if (!enemiesInRange.empty()) {
      if (type != 2) {
        std::cout << "Attacking" << std::endl;
        (*enemiesInRange.front()).getHit(dmg); // Hit the enemy
        target = &(*enemiesInRange.front());

        if (type == 1) {
          // For Type 1 tower, start an attack animation
          attacking = true;
          attackSprite.setPosition(position);
          attackTargetPosition = target->position;
        }
      } else if (type == 2) {
        for (auto &enemyIt : enemiesInRange)
          enemyIt->slow();
      }
    }
    cooldownClock.restart();
  }
}
