// Referenced in game. Needs to be implemented. Here you can add constants that
// slightly affect the game configuration. The idea is that some variables that
// can be changed are located in a single file.
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <SFML/Graphics.hpp>

extern const int windowWidth;
extern const int windowHeight;
extern const int tileSize;
extern const std::vector<int> towerPrices;
extern const std::vector<int> towerRanges;
extern void scaleSprite(sf::Sprite &sprite, const sf::Texture &texture);

#endif // CONSTANTS_HPP
