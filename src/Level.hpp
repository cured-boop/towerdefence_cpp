#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Pos.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm> // For std::find
#include <iostream>  // For testing, you can remove this in production code
#include <vector>

class Level {
public:
  Level(const std::vector<std::vector<int>> &layout, int width = 1000,
        int height = 1000);

  const std::vector<std::vector<int>> &getLayout() const;
  const std::vector<Pos> &getRoad() const;

  bool pointOnRoad(const Pos &cursor) const;
  bool oob(const Pos &cursor) const;

  void draw(sf::RenderWindow &window);

private:
  std::vector<std::vector<int>> layout;
  int width;
  int height;
  std::vector<Pos> road;
  sf::Texture grassTexture;
  sf::Texture roadTexture;
  sf::Sprite grassSprite;
  sf::Sprite roadSprite;
  const int tileSize = 100;

  void findRoad();
};

#endif // LEVEL_HPP