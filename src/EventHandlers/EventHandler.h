#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SFML/Window/Event.hpp>
#include "GameObjects/GameObject.h"

class EventHandler : public GameObject {
public:
  virtual void handle(const sf::Event& event) = 0;

  bool autoDelete { false };
};

#endif // EVENTHANDLER_H
