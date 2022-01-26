#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "GameObjects/Entity.h"
#include "Handlers/EventHandler.h"
#include "GameObjects/Map.h"
#include "Handlers/CollisionHandler.h"

class PlayerController final : public EventHandler, public CollisionHandler {
public:
  PlayerController(class Entity* entity, class Map* map) {
    player = entity;
    this->map = map;
  }

  void handle(const sf::Event& event) override {
    if (event.type == sf::Event::KeyPressed) {
      if (player) {
        if (event.key.code == sf::Keyboard::S)
          player->setDirection(Entity::Down);
        else if (event.key.code == sf::Keyboard::W)
          player->setDirection(Entity::Up);
        else if (event.key.code == sf::Keyboard::A)
          player->setDirection(Entity::Left);
        else if (event.key.code == sf::Keyboard::D)
          player->setDirection(Entity::Right);
      }
    }
  }

  class Entity* player {nullptr};
  class Map* map {nullptr};

  // CollisionHandler interface
public:
  void onCollision(PhysObject* obj1, PhysObject* obj2) override {
    Entity* other = nullptr;

    if (obj1 == (void*)player) {
      other = dynamic_cast<Entity*>(obj2);
    }
    else if (obj2 == (void*)player) {
      other = dynamic_cast<Entity*>(obj1);
    }
    else return;

    if (other->type == Entity::Brick) {
      player->setDirection(Entity::Stoped);

      for (Entity& entity : map->layers[0]) {
        if (entity.type == Entity::LightBrick)
          entity.type = Entity::Brick;
      }
    }
    else if (other->type == Entity::None)
      other->type = Entity::LightBrick;
  }
  void offCollision(PhysObject* obj1, PhysObject* obj2) override {

  }
};

#endif // PLAYERCONTROLLER_H
