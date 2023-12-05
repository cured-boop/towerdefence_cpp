// Referenced in game. Needs to be implemented. Here you can add constants that
// slightly affect the game configuration. The idea is that some variables that
// can be changed are located in a single file.
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <SFML/Graphics.hpp>

extern const int windowWidth;
extern const int windowHeight;
extern const int menuHeight;
extern const int tileSize;
extern const int tileSizeOffset;
extern const std::vector<int> towerPrices;
extern const std::vector<int> towerRanges;
extern const std::vector<int> enemyHPs;
extern const std::vector<int> enemySpeeds;
extern const std::vector<int> enemyMoneys;
extern void scaleSprite(sf::Sprite &sprite);
extern void centerSprite(sf::Sprite &sprite);
extern sf::Vector2f tileToPosition(sf::Vector2i);
extern sf::Vector2f tileToPosition(int x, int y);

#endif // CONSTANTS_HPP
