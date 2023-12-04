#ifndef TOWER_HPP
#define TOWER_HPP

#include "Enemy.hpp"
#include <vector>

class Tower {
public:
  int dmg;
  int range;
  int cost;
  int delay;
  sf::Vector2f position;

  Tower(int dmg, int range, int cost, sf::Vector2f position);

  std::vector<Enemy> withinRange(std::vector<Enemy> &enemies);

  void attack(std::vector<Enemy> &enemies);

  void draw(sf::RenderWindow &window);

private:
  sf::Clock cooldownClock;
  sf::Texture texture;
  sf::Sprite sprite;
};
/*
class mainInfo {
public:
  int dmg;
  int range;
  int cost;

  mainInfo(int dmg, int range, int cost);
};

class towersToSaveState {
public:
  Game *game;
  std::map<int, mainInfo> Alltowers;

  towersToSaveState(Game *game, std::vector<Json::Value> JSONtower);

  std::optional<Tower> wrap(int Type, Pos pos = Pos(0, 0));
};
*/
#endif // TOWER_HPP