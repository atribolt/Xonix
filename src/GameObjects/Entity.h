#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System/Vector2.hpp>

class Entity {
public:
  enum Directions : char {
    Up, 
    Down,
    Left,
    Right
  };
  
  
  
  float speed;
  Directions moveDirection;
  sf::Vector2i pos;
};

#endif // ENTITY_H
