// reference in Game, needs to be implemented. Represents enemies.
#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy {
public:
  double speed;
  sf::Vector2f position;
  int hp;

  Enemy(const std::vector<sf::Vector2i> &path, double speed = 50.0,
        int hp = 100);

  void move(float deltaTime);

  int currentPathIndex;

  void getHit(int dmg);

  void setPosition(sf::Vector2f);

  void draw(sf::RenderWindow &window); // Uses tileSize and pos to calculate the
                                       // location on screen

  std::vector<sf::Vector2i> path;

  void setPath(std::vector<sf::Vector2i> path);

private:
  sf::Texture enemyTexture;
  sf::Sprite enemySprite;
};

#endif