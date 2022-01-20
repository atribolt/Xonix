#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/System/Vector2.hpp>

class Block {
public:
  enum Type {
    Ground,
    Border,
    LightBorder
  };
  
  Type type;
  sf::Vector2i position;
};

#endif // BLOCK_H
