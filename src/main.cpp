#include <thread>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "GameSettings.h"
#include "Logging/Log.h"
#include "Logging/Logger.h"


static Log deflog("Main");


int main(int argc, char** argv) {
  Logger::instance().init(new LogImplement());
  Logger::instance().setLevel(LogLevel::Debug);

  Game& game = Game::instance();
  GameSettings& settings = GameSettings::instance();


  sf::VideoMode vMode(settings.windowWidth(), settings.windowHeight());
  int windowStyle = sf::Style::Close;
  sf::RenderWindow window(vMode, settings.windowTitle(), windowStyle);

  do {
    sf::Event ev;
    if (window.pollEvent(ev))
      Game::instance().event(ev);

    window.clear();
    window.draw(game);
    window.display();

    if (!game.isOpen()) {
      window.close();
    }
  } while (window.isOpen());

  return 0;
}
