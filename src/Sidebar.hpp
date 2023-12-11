#ifndef SIDEBAR_HPP
#define SIDEBAR_HPP

#include "Tower.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Sidebar {
public:
    Sidebar(float width, const sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
    int selectTower(int money, sf::Vector2f position);
    float getWidth();

private:
    float width;
    sf::RectangleShape background;

    sf::Texture textureCat0, textureCat1, textureCat2;
    sf::Sprite spriteCat0, spriteCat1, spriteCat2;

    int selectedTower;
    std::vector<sf::Text> towerPricesTexts;
    sf::Font font;
};

#endif // SIDEBAR_HPP
