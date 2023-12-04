#include "Tower.hpp"
#include "Constants.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

Tower::Tower(int _dmg, int _range, int _cost, sf::Vector2f _position)
    : dmg(_dmg), range(_range), cost(_cost), position(_position) {

  // Load textures
  if (!texture.loadFromFile("src/assets/cat.png")) {
    // Handle error
  }

  // Set textures to sprites
  sprite.setTexture(texture);

  // Calculate scale factors
  float scaleX = static_cast<float>(tileSize) / texture.getSize().x;
  float scaleY = static_cast<float>(tileSize) / texture.getSize().y;
  sprite.setScale(scaleX, scaleY);
  sprite.setPosition(position.x, position.y);
}

void Tower::draw(sf::RenderWindow &window) { window.draw(sprite); }

std::vector<Enemy> Tower::withinRange(std::vector<Enemy> &enemies) {
  std::vector<Enemy> result;
  for (auto &enemy : enemies) {
    double distance = std::sqrt(std::pow(enemy.position.x - position.x, 2) +
                                std::pow(enemy.position.y - position.y, 2));
    if (distance < range) {
      result.push_back(enemy);
    }
  }
  return result;
}

void Tower::attack(std::vector<Enemy> &enemies) {
  if (cooldownClock.getElapsedTime().asSeconds() >= delay) {
    auto enemiesInRange = withinRange(enemies);
    if (!enemiesInRange.empty()) {
      enemiesInRange.front().getHit(dmg);
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