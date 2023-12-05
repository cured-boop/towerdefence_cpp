#include "State.hpp"
#include "Constants.hpp"
#include <iostream>

State::State(int _currentWave, int _gold, int _wavesTotal)
    : currentWave(_currentWave), gold(_gold), wavesTotal(_wavesTotal) {

  if (!font.loadFromFile("src/assets/arial.ttf")) {
    // Handle error
  }

  moneyText.setFont(font);
  moneyText.setCharacterSize(20);
  moneyText.setPosition(windowWidth - 140, windowHeight - 40);
  moneyText.setStyle(sf::Text::Bold);
  moneyText.setFillColor(sf::Color(255, 106, 168));

  waveText.setFont(font);
  waveText.setCharacterSize(20);
  waveText.setPosition(windowWidth - 140, windowHeight - 90);
  waveText.setStyle(sf::Text::Bold);
  waveText.setFillColor(sf::Color(255, 106, 168));
}

int State::money() { return gold; }

bool State::isFinished() { return currentWave > wavesTotal; }

void State::addMoney(int amount) { gold += amount; }

void State::draw(sf::RenderWindow &window) {
  moneyText.setString("Money: " + std::to_string(gold));
  waveText.setString("Wave: " + std::to_string(currentWave) + "/" +
                     std::to_string(wavesTotal));
  window.draw(moneyText);
  window.draw(waveText);
}
/*
void State::loadStatus(const Json::Value& json) {
    gold = json["gold"].asInt();
    hp = json["hp"].asInt();
}*/