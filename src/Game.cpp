#include "Game.hpp"
#include "Constants.hpp"
#include "SaverLoader.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using json = nlohmann::json;

// Define game state
SaverLoader gameState = SaverLoader();

// Call the loadConfig function to load the configuration into a JSON object
json config = gameState.loadConfig();

// Access the dara arrays
json levels = config["levels"];
json paths = config["paths"];
json towers = config["towers"];
json golds = config["gold"];
// Output the levels array
// std::cout << "Levels:" << std::endl;

//const std::vector<std::vector<int>> layout = levels[0];

/*
const std::vector<sf::Vector2i> path = {
    {1, 7}, {1, 6}, {1, 5}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4},
    {5, 3}, {5, 2}, {4, 2}, {3, 2}, {3, 1}, {3, 0}, {3, -1}};
*/

Enemy enemy0 = Enemy(0);

Enemy enemy1 = Enemy(1);

Enemy enemy2 = Enemy(2);

std::vector<Wave> waves = {Wave({enemy1, enemy0, enemy2}), Wave({enemy1}),
                           Wave({enemy1})};
auto tower0 = towers[0];
auto tower1 = towers[1];
auto tower2 = towers[2];
Tower cat0 = Tower(tower0["damage"], tower0["range"], tower0["cost"],
                   tower0["delay"], 0);
Tower cat1 = Tower(tower1["damage"], tower1["range"], tower1["cost"],
                   tower1["delay"], 1);
Tower cat2 = Tower(tower2["damage"], tower2["range"], tower2["cost"],
                   tower2["delay"], 2);

std::vector<Tower> purchasedTowers;

Game::Game(sf::RenderWindow &win): window(win), sidebar(200, window), selectedTower(-1) {
  

  // Load tower textures and create sprites for each tower type
  if (textureCat0.loadFromFile("src/assets/cat0.png")) {
    std::cout << "cat0 loaded" << std::endl;
    spriteCat0.setTexture(textureCat0);
    scaleSprite(spriteCat0);
    centerSprite(spriteCat0);
    towerSprites.push_back(spriteCat0);
  }
  if (textureCat1.loadFromFile("src/assets/cat1.png")) {
    std::cout << "cat1 loaded" << std::endl;
    spriteCat1.setTexture(textureCat1);
    scaleSprite(spriteCat1);
    centerSprite(spriteCat1);
    towerSprites.push_back(spriteCat1);
  }
  if (textureCat2.loadFromFile("src/assets/cat2.png")) {
    std::cout << "cat2 loaded" << std::endl;
    spriteCat2.setTexture(textureCat2);
    scaleSprite(spriteCat2);
    centerSprite(spriteCat2);
    towerSprites.push_back(spriteCat2);
  }

  // Initialize GUI elements:
  // Load font
  if (!font.loadFromFile("src/assets/bubblegum.ttf")) {
    std::cout << "font loaded" << std::endl;
    // Handle error
  }
  createLossScreenButtons();

  // TODO: Read tower data from file and push to the vector:
  availableTowers.push_back(cat0);
  availableTowers.push_back(cat1);
  availableTowers.push_back(cat2);
  // TODO: Read levelnumber from save file and call load(levelnumber)
  load(levelNumber);
}

void Game::load(int levelNumber) {
  std::vector<sf::Vector2i> path;
  for (const auto& p: paths[levelNumber]) {
    sf::Vector2i vec(p[0], p[1]);
    path.push_back(vec);
  }
  // TODO: Load the level from a file according to the levelNumber
  //levelNumber = levelNumber;
  level.initialize(levels[levelNumber], path, waves, purchasedTowers);

  // TODO: Read state from a save file
  int currentWave = 1;
  int gold = golds;
  int totalWaves = level.getWaves().size();
  state.initialize(currentWave, gold, totalWaves);

  isLost = false;
}

void Game::update() {
  sf::Event event;
  while (window.pollEvent(event)) {
    handleEvents(event); // Pass each event to the handler
  }

  if (isLost)
    return;

  sf::Time elapsed = gameClock.restart();
  float deltaTime = elapsed.asSeconds();
  updateTowers();
  updateEnemies(deltaTime);
  // Any other update logic (e.g., check game over, update state)
  level.update(state);
}

void Game::draw() {
  // Draw level
  level.draw(window);
  sidebar.draw(window);

  // Draw each enemy
  for (auto &enemy : level.enemies) {
    enemy.draw(window);
  }

  // Draw each tower
  for (auto &tower : level.towers) {
    tower.draw(window);
  }

  state.draw(window);

  if (selectedTower >= 0) {
    window.draw(rangeIndicator);              // Draw the range indicator
    window.draw(towerSprites[selectedTower]); // Draw the cursor sprite
  }

  if (isLost) {
    drawGameLossScreen();
  }
  if (level.getLevelWon())
    drawGameWinScreen();
}

void Game::handleEvents(const sf::Event &event) {

  if (event.type == sf::Event::Closed) {
    window.close();
  }

  // The tower sprite follows the cursor when placing it
  if (selectedTower >= 0) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f position = sf::Vector2f(mousePosition.x, mousePosition.y);
    towerSprites[selectedTower].setPosition(position);
    rangeIndicator.setPosition(position); // Update range indicator position
  }

  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      std::cout << "getLevelWon(): " << level.getLevelWon() << std::endl;
      if (isLost) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (isOnButton(exitButton, mousePos)) {
          window.close();
        } else if (isOnButton(restartButton, mousePos)) {
          load(levelNumber);
        }
      }
      else if (level.getLevelWon() == 1) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (isOnButton(nextButton, mousePos)) {
          std::cout << "next" << std::endl;
          levelNumber++;
          load(levelNumber);
          level.setLevelWon(false);
        }
      }
      else {
        handleMouseClick(event.mouseButton.x, event.mouseButton.y);
      }
    }
  }
}

void Game::updateEnemies(float deltaTime) {
  level.enemies.remove_if([this, deltaTime](Enemy &enemy) {
    if (enemy.isDead) {
      state.addMoney(enemy.money);
      return true; // Remove the enemy and add its money to the player
    } else if (enemy.finished) {
      isLost = true;
      return false;
    } else {
      enemy.move(deltaTime);
      return false; // Keep and move the enemy
    }
  });
}

void Game::updateTowers() {
  for (auto &tower : level.towers) {
    tower.attack(level.enemies);
  }
}

void Game::handleMouseClick(int x, int y) {
  // Check if the click is within the sidebar
  std::cout << "Checking if the click was within sidebar" << std::endl;
  if (x >= window.getSize().x - sidebar.getWidth()) {
    std::cout << "The click was within sidebar" << std::endl;
    // Handle sidebar interaction
    selectedTower = sidebar.selectTower(state.money(), sf::Vector2f(x, y));
    if (selectedTower >= 0) {
      towerSprites[selectedTower].setPosition(x, y);

      // Initialize the range indicator
      rangeIndicator.setRadius(towerRanges[selectedTower]);
      rangeIndicator.setFillColor(
          sf::Color(255, 255, 255, 128)); // Half-transparent white
      rangeIndicator.setOrigin(
          rangeIndicator.getRadius(),
          rangeIndicator.getRadius()); // Set origin to the center of the circle
      rangeIndicator.setPosition(x, y);
    }
  } else {
    // Handle map interaction
    // Check if a tower is selected and the click is on a valid position
    std::cout << "Checking if the click was on a valid position (and tower is "
                 "selected)"
              << std::endl;
    if (selectedTower >= 0 && isValidPosition(x, y)) {
      // Place the tower on the map
      std::cout << "Placing the tower" << std::endl;
      Tower tower = availableTowers[selectedTower];
      tower.setPosition(level.calculateTile(x, y));
      level.towers.push_back(tower);
      // Pay for the tower
      state.addMoney(-towerPrices[selectedTower]);
      // Reset selected tower
      selectedTower = -1;
    }
  }
}

bool Game::isValidPosition(int x, int y) {
  return level.isEmpty(level.calculateTile(x, y));
}

void Game::drawGameLossScreen() {
  // Create a semi-transparent overlay
  sf::RectangleShape overlay(
      sf::Vector2f(window.getSize().x, window.getSize().y));
  overlay.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black

  // Create a text message
  createWinScreenButtons();
  sf::Text message;
  message.setFont(font);
  message.setString("Game Over! You Lost!");
  message.setCharacterSize(50); // or another appropriate size
  message.setFillColor(sf::Color::White);
  message.setPosition(
      window.getSize().x / 2.f - message.getGlobalBounds().width / 2.f,
      window.getSize().y / 2.f - message.getGlobalBounds().height / 2.f);

  // Draw the overlay and message
  window.draw(overlay);
  window.draw(message);
  window.draw(exitButton);
  window.draw(exitButtonText);
  window.draw(restartButton);
  window.draw(restartButtonText);
}
void Game::drawGameWinScreen() {
  // Create a semi-transparent overlay
  sf::RectangleShape overlay(
      sf::Vector2f(window.getSize().x, window.getSize().y));
  overlay.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black

  // Create a text message
  createWinScreenButtons();
  sf::Text message;
  message.setFont(font);
  message.setString("Level Complete!");
  message.setCharacterSize(50); // or another appropriate size
  message.setFillColor(sf::Color::White);
  message.setPosition(
      window.getSize().x / 2.f - message.getGlobalBounds().width / 2.f,
      window.getSize().y / 2.f - message.getGlobalBounds().height / 2.f);

  // Draw the overlay and message
  window.draw(overlay);
  window.draw(message);
  window.draw(nextButton);
  window.draw(nextButtonText);
}

void Game::createLossScreenButtons() {
  // Assume font is already loaded

  // Styling for the buttons
  sf::Color buttonFillColor =
      sf::Color(100, 100, 250); // Choose a pleasant color
  sf::Color buttonOutlineColor = sf::Color::Black;
  float buttonOutlineThickness = 2.0f;

  // Exit Button
  exitButton.setSize(sf::Vector2f(100, 50));
  exitButton.setPosition(window.getSize().x / 2 - 150,
                         window.getSize().y / 2 + 100);
  exitButton.setFillColor(buttonFillColor);
  exitButton.setOutlineColor(buttonOutlineColor);
  exitButton.setOutlineThickness(buttonOutlineThickness);

  exitButtonText.setFont(font);
  exitButtonText.setString("Exit");
  exitButtonText.setCharacterSize(20);
  exitButtonText.setFillColor(sf::Color::White);
  // Center the text in the button
  sf::FloatRect textRect = exitButtonText.getLocalBounds();
  exitButtonText.setOrigin(textRect.left + textRect.width / 2.0f,
                           textRect.top + textRect.height / 2.0f);
  exitButtonText.setPosition(
      exitButton.getPosition().x + exitButton.getSize().x / 2.0f,
      exitButton.getPosition().y + exitButton.getSize().y / 2.0f);

  // Restart Button
  restartButton.setSize(sf::Vector2f(100, 50));
  restartButton.setPosition(window.getSize().x / 2 + 50,
                            window.getSize().y / 2 + 100);
  restartButton.setFillColor(buttonFillColor);
  restartButton.setOutlineColor(buttonOutlineColor);
  restartButton.setOutlineThickness(buttonOutlineThickness);

  restartButtonText.setFont(font);
  restartButtonText.setString("Restart");
  restartButtonText.setCharacterSize(20);
  restartButtonText.setFillColor(sf::Color::White);
  // Center the text in the button
  textRect = restartButtonText.getLocalBounds();
  restartButtonText.setOrigin(textRect.left + textRect.width / 2.0f,
                              textRect.top + textRect.height / 2.0f);
  restartButtonText.setPosition(
      restartButton.getPosition().x + restartButton.getSize().x / 2.0f,
      restartButton.getPosition().y + restartButton.getSize().y / 2.0f);
}
void Game::createWinScreenButtons() {
  // Assume font is already loaded

  // Styling for the buttons
  sf::Color buttonFillColor =
      sf::Color(100, 100, 250); // Choose a pleasant color
  sf::Color buttonOutlineColor = sf::Color::Black;
  float buttonOutlineThickness = 2.0f;

  // Next button
  nextButton.setSize(sf::Vector2f(100, 50));
  nextButton.setPosition(window.getSize().x / 2 - 50,
                         window.getSize().y / 2 + 100);
  nextButton.setFillColor(buttonFillColor);
  nextButton.setOutlineColor(buttonOutlineColor);
  nextButton.setOutlineThickness(buttonOutlineThickness);

  nextButtonText.setFont(font);
  nextButtonText.setString("Next");
  nextButtonText.setCharacterSize(20);
  nextButtonText.setFillColor(sf::Color::White);
  // Center the text in the button
  sf::FloatRect textRect = nextButtonText.getLocalBounds();
  nextButtonText.setOrigin(textRect.left + textRect.width / 2.0f,
                           textRect.top + textRect.height / 2.0f);
  nextButtonText.setPosition(
      nextButton.getPosition().x + nextButton.getSize().x / 2.0f,
      nextButton.getPosition().y + nextButton.getSize().y / 2.0f);
}

bool Game::isOnButton(const sf::RectangleShape &button,
                      const sf::Vector2f &mousePos) {
  return button.getGlobalBounds().contains(mousePos);
}

