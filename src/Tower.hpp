#ifndef TOWER_HPP
#define TOWER_HPP

#include "Enemy.hpp"
#include <list>
#include <vector>

class Tower {
public:
  int dmg;
  int range;
  int cost;
  int delay;
  int type;
  sf::Vector2f position;

  Tower(int dmg, int range, int cost, int delay, int type);

  std::vector<std::list<Enemy>::iterator>
  withinRange(std::list<Enemy> &enemies);

  void attack(std::list<Enemy> &enemies);

  void draw(sf::RenderWindow &window);

  void setPosition(sf::Vector2i);

private:
  sf::Clock cooldownClock;
  sf::Texture towerTexture;
  sf::Texture attackTexture;
  sf::Sprite towerSprite;
  sf::Sprite attackSprite;
  Enemy *target;
  bool attacking = false; // Indicates if the tower is currently attacking
  sf::Vector2f attackTargetPosition; // Target position for attack animation
  float attackSpeed = 2.0f;          // Speed of attack animation
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