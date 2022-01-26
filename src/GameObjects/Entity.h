#ifndef ENTITY_H
#define ENTITY_H

#include "GameObjects/PhysObjects.h"
#include "GameSettings.h"

class Entity final : public PhysObject {
public:
  enum Type : char {
    Brick,
    LightBrick,
    Enemy,
    Player,
    Destroy,
    None
  };

  Entity(Type t, float speed = 0.f)
    : type(t)
  {
    width = GameSettings::instance().cellWidth();
    height = GameSettings::instance().cellHeight();

    this->speed = speed;
  }

  Type type;
};

#endif // PLAYER_H
