// Referenced in Game. Needs to be implemented. Represents the current game
// state. class Tower; // Forward declaration
#ifndef OVERALL_HPP
#define OVERALL_HPP
#include <SFML/Graphics.hpp>

class State {
public:
  State();
  bool isFinished();
  void addMoney(int amount);
  int money();
  void draw(sf::RenderWindow &window);
  void nextWave();
  void initialize(int currentWave, int gold, int wavesTotal);
  // void loadStatus(const Json::Value &json);

private:
  int currentWave;
  int gold;
  sf::Font font;
  sf::Text moneyText;
  sf::Text waveText;
  int wavesTotal;
};

#endif // OVERALL_HPP