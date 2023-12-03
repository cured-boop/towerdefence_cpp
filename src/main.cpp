#include "Game.hpp"
#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 700), "Tower Defense Game");

  sf::Font font;
  if (!font.loadFromFile("src/assets/arial.ttf")) {
    // Handle error
  }

  sf::Text startText("Start", font, 20);
  startText.setPosition(350, 200);

  sf::Text exitText("Exit", font, 20);
  exitText.setPosition(350, 250);

  bool gameStarted = false;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        if (startText.getGlobalBounds().contains(
                window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
          gameStarted = true;
        }

        if (exitText.getGlobalBounds().contains(
                window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
          window.close();
        }
      }
    }

    window.clear();
    window.draw(startText);
    window.draw(exitText);
    window.display();

    if (gameStarted) {
      break;
    }
  }

  // Initialize the game
  Game game = Game(window);

  while (window.isOpen() && gameStarted) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      game.update(); // Game "tick"
    }

    window.clear();
    game.draw(); // Make game stuff appear on the screen
    window.display();
  }

  return 0;
}
