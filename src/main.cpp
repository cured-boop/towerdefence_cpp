#include "Constants.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>

int main() {

  sf::Texture backgroundTexture;
  if (!backgroundTexture.loadFromFile("src/assets/menubg.png")) {
    // Handle error
  }

  sf::Sprite backgroundSprite(backgroundTexture);
  backgroundSprite.setColor(
      sf::Color(255, 255, 255, 128)); // Set half transparency

  sf::RenderWindow menu(sf::VideoMode(menuHeight * 1.75, menuHeight),
                        "Paws and Claws: Mouse Invasion");

  menu.setPosition(sf::Vector2i(300, 150));

  // Scale the background sprite to fit the window
  backgroundSprite.setScale(
      float(menu.getSize().x) / backgroundTexture.getSize().x,
      float(menu.getSize().y) / backgroundTexture.getSize().y);

  sf::Font font;
  if (!font.loadFromFile("src/assets/bubblegum.ttf")) {
    // Handle error
  }

  sf::Text startText("Start", font, 40); // Larger font size
  startText.setFillColor(sf::Color::White);
  startText.setStyle(sf::Text::Bold);
  sf::FloatRect startBounds = startText.getLocalBounds();
  startText.setOrigin(startBounds.left + startBounds.width / 2.0f,
                      startBounds.top + startBounds.height / 2.0f);
  startText.setPosition(menu.getSize().x / 2.0f, menu.getSize().y / 2.0f - 50);

  sf::Text exitText("Exit", font, 40); // Larger font size
  exitText.setFillColor(sf::Color::White);
  exitText.setStyle(sf::Text::Bold);
  sf::FloatRect exitBounds = exitText.getLocalBounds();
  exitText.setOrigin(exitBounds.left + exitBounds.width / 2.0f,
                     exitBounds.top + exitBounds.height / 2.0f);
  exitText.setPosition(menu.getSize().x / 2.0f, menu.getSize().y / 2.0f + 50);

  bool gameStarted = false;
  while (menu.isOpen()) {
    sf::Event event;
    while (menu.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        menu.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        if (startText.getGlobalBounds().contains(
                menu.mapPixelToCoords(sf::Mouse::getPosition(menu)))) {
          gameStarted = true;
        }

        if (exitText.getGlobalBounds().contains(
                menu.mapPixelToCoords(sf::Mouse::getPosition(menu)))) {
          menu.close();
        }
      }
    }

    menu.clear();
    menu.draw(backgroundSprite);
    menu.draw(startText);
    menu.draw(exitText);
    menu.display();

    if (gameStarted) {
      break;
    }
  }

  // Initialize the game

  menu.close();
  // Set the new size for the window
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                          "Paws and Claws: Mouse Invasion");

  window.setPosition(sf::Vector2i(300, 150));
  Game game = Game(window);

  while (window.isOpen() && gameStarted) {
    game.update(); // Game "tick", handles events internally
    window.clear();
    game.draw(); // Make game stuff appear on the screen
    window.display();
  }

  return 0;
}
