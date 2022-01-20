#ifndef EXITGAME_H
#define EXITGAME_H

#include "EventHandlers/EventHandler.h"

class ExitGame final : public EventHandler {
public:
  ExitGame();

  void handle(const sf::Event& event) override;
};

#endif // EXITGAME_H
