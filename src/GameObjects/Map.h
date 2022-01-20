#ifndef MAP_H
#define MAP_H

#include <vector>

#include "Block.h"

class Map {
public:
  Map(sf::Vector2i size);
  
  Block& operator[](const sf::Vector2i& cell);
  
  const sf::Vector2i& size() const;
  const Block& operator[](const sf::Vector2i& cell) const;
  
private:
  sf::Vector2i _size;
  std::vector<Block> _map;
};

#endif // MAP_H
