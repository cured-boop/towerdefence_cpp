// reference in Game, needs to be implemented. Represents enemies.
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy {
public:
  double speed;
  sf::Vector2f position;
  int hp;

  Enemy(int type);

  void initialize(std::vector<sf::Vector2i> path);

  void move(float deltaTime);

  size_t currentPathIndex;

  void getHit(int dmg);

  int type;

  float distanceToNextTile;

  bool finished;

  void draw(sf::RenderWindow &window);

  std::vector<sf::Vector2i> path;

  void setPath(std::vector<sf::Vector2i> path);

  void die();

  bool isDead;

  void slow();

  int money;

private:
  sf::Texture enemyTexture;
  sf::Sprite enemySprite;
  sf::Clock deathClock; // Adds a delay before dying
  sf::Clock slowClock;
  bool dying;
  float speedModifier;
};

#endif