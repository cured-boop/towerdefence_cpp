#include "State.hpp"
#include "Constants.hpp"
#include <iostream>

State::State() {

  if (!font.loadFromFile("src/assets/bubblegum.ttf")) {
    // Handle error
  }

  moneyText.setFont(font);
  moneyText.setCharacterSize(30);
  moneyText.setStyle(sf::Text::Bold);
  moneyText.setPosition(windowWidth - 180, windowHeight - 40);
  moneyText.setStyle(sf::Text::Bold);
  moneyText.setFillColor(sf::Color(19, 21, 54));

  waveText.setFont(font);
  waveText.setCharacterSize(30);
  moneyText.setStyle(sf::Text::Bold);
  waveText.setPosition(windowWidth - 180, windowHeight - 90);
  waveText.setStyle(sf::Text::Bold);
  waveText.setFillColor(sf::Color(19, 21, 54));
}

void State::initialize(int _currentWave, int _gold, int _wavesTotal) {
  currentWave = _currentWave;
  gold = _gold;
  wavesTotal = _wavesTotal;
}

int State::money() { return gold; }

bool State::isFinished() { return currentWave > wavesTotal; }

void State::nextWave() { currentWave++; }

void State::addMoney(int amount) { gold += amount; }

void State::draw(sf::RenderWindow &window) {
  moneyText.setString("Money: " + std::to_string(gold));
  waveText.setString(
      "Wave: " + std::to_string(std::min(currentWave, wavesTotal)) + "/" +
      std::to_string(wavesTotal));
  window.draw(moneyText);
  window.draw(waveText);
}
/*
void State::loadStatus(const Json::Value& json) {
    gold = json["gold"].asInt();
    hp = json["hp"].asInt();
}*/