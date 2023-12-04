// Referenced in Game. Needs to be implemented. Represents the current game
// state. class Tower; // Forward declaration
#ifndef OVERALL_HPP
#define OVERALL_HPP
#include "Level.hpp"
#include <SFML/Graphics.hpp>

class State {
public:
  State(int currentWave, int gold, int wavesTotal);
  bool isFinished();
  void addMoney(int amount);
  int money();
  void draw(sf::RenderWindow &window);
  // void loadStatus(const Json::Value &json);

private:
  int currentWave;
  int gold;
  int wavesTotal;
  sf::Font font;
  sf::Text moneyText;
  sf::Text waveText;
};

#endif // OVERALL_HPP