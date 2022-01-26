#ifndef ENEMYCOLLISION_H
#define ENEMYCOLLISION_H

#include "Handlers/CollisionHandler.h"
#include "GameObjects/Entity.h"
#include "Game.h"

class EnemyCollision final : public CollisionHandler {
public:
  void onCollision(PhysObject* obj1, PhysObject* obj2) override {
    Entity* en1 = dynamic_cast<Entity*>(obj1);
    Entity* en2 = dynamic_cast<Entity*>(obj2);

    Entity* enemy = nullptr;
    Entity* other = nullptr;

    if (en1->type == Entity::Enemy && en2->type != Entity::Enemy) {
      enemy = en1;
      other = en2;
    }
    else if (en2->type == Entity::Enemy && en1->type != Entity::Enemy) {
      enemy = en2;
      other = en1;
    }
    else return;

    switch (other->type) {
      case Entity::Brick:
        enemy->direction *= -1.f;
        break;
      case Entity::LightBrick:
      case Entity::Player:
        Game::instance().gameOver();
        break;
      default:
        break;
    }
  }
  void offCollision(PhysObject* obj1, PhysObject* obj2) override {}
};

#endif // ENEMYCOLLISION_H
