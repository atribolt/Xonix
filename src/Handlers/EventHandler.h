#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SFML/Window/Event.hpp>

class EventHandler {
public:
  EventHandler() {}
  virtual ~EventHandler() {}

  virtual void handle(const sf::Event& event) = 0;
};

#endif // EVENTHANDLER_H
