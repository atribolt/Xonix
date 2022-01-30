#ifndef PHYSOBJECTS_H
#define PHYSOBJECTS_H

#include <SFML/Graphics/RectangleShape.hpp>

class PhysObject : public sf::FloatRect {
public:
  enum Type {
    Static,
    Dynamic
  };

  enum Direction : char {
    Stoped = 0,
    Up = 1,
    Down = 3,
    Left = 2,
    Right = 4
  };

  PhysObject(Type type = Static, float speed = 0.f, Direction dir = Stoped)
    : objType(type)
    , speed(speed)
  {
    setDirection(dir);
  }
awe
  virtual ~PhysObject() {}

  void setDirection(Direction dir) {
    switch(dir) {
      case PhysObject::Direction::Stoped: {
        direction.x = direction.y = 0;
        break;
      }
      case PhysObject::Direction::Up:
      case PhysObject::Direction::Down: {
        direction.x = 0;
        direction.y = dir - 2;
        break;
      }
      case PhysObject::Direction::Left:
      case PhysObject::Direction::Right: {
        direction.y = 0;
        direction.x = dir - 3;
        break;
      }
    }
  }

  sf::Vector2f topLeft() const { return {left, top}; }
  sf::Vector2f topRight() const { return {left + width, top}; }
  sf::Vector2f bottomLeft() const { return {left, top + height}; }
  sf::Vector2f bottomRight() const { return {left + width, top + height}; }

  sf::Vector2f center() const {
    return { left + width / 2.f, top + height / 2.f };
  }


  void move(const sf::Vector2f& pos) {
    left += pos.x;
    top += pos.y;
  }

  Type objType;
  float speed {0.f};
  sf::Vector2f direction {0, 0};
};

#endif // PHYSOBJECTS_H
