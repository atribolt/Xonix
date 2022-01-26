#ifndef CLOSEHANDLER_H
#define CLOSEHANDLER_H

#include "Handlers/EventHandler.h"

#include "Game.h"

class CloseHandler final : public EventHandler {
public:
  ~CloseHandler() override {};

  void handle(const sf::Event& event) override {
    if (event.type == sf::Event::Closed)
      Game::instance().exit();

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::R)
        Game::instance().restart();
    }
  }
};


#endif // CLOSEHANDLER_H
