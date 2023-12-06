#include "Tower.hpp"
#include "Constants.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

Tower::Tower(int _dmg, int _range, int _cost, int _delay)
    : dmg(_dmg), range(_range), cost(_cost), delay(_delay) {

  // Load textures
  if (!towerTexture.loadFromFile("src/assets/cat0.png")) {
    // Handle error
  }
  if (!attackTexture.loadFromFile("src/assets/claw.png")) {
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
  if (cooldownClock.getElapsedTime().asSeconds() < delay / 2) {
    if (target && !target->isDead) {
      attackSprite.setPosition(target->position);
      window.draw(attackSprite);
    }
  } else
    target = nullptr;
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
      std::cout << "Attacking" << std::endl;
      (*enemiesInRange.front())
          .getHit(dmg); // Dereference iterator to modify actual enemy
      target = &(*enemiesInRange.front());
      cooldownClock.restart();
    }
  }
}
/*

mainInfo::mainInfo(int dmg, int range, int cost)
    : dmg(dmg), range(range), cost(cost) {}

towersToSaveState::towersToSaveState(Game *game,
                                     std::vector<Json::Value> JSONtower)
    : game(game) {
  for (size_t i = 0; i < JSONtower.size(); ++i) {
    auto towerInfo = JSONtower[i];
    int dm = towerInfo["dmg"].asInt();
    int rang = towerInfo["range"].asInt();
    int cos = towerInfo["cost"].asInt();
    Alltowers[i + 1] = mainInfo(dm, rang, cos);
  }
}*/