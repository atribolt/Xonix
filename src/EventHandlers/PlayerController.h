#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H


#include <memory>
#include "EventHandlers/EventHandler.h"


class Entity;
using EntityPtr = std::shared_ptr<Entity>;

class PlayerController final : public EventHandler {
public:
  PlayerController(EntityPtr player);
  
  void handle(const sf::Event& ev) override;
  
private:
  EntityPtr _player;
};

#endif // PLAYERCONTROLLER_H
