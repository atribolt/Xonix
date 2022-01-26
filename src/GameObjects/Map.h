#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "GameSettings.h"
#include "GameObjects/Entity.h"

class Map final : public sf::Drawable {
public:
  Map() {}

  void init() {
    layers.clear();

    GameSettings& setts = GameSettings::instance();

    mapSize.x = setts.windowWidth() / setts.cellWidth();
    mapSize.y = setts.windowHeight() / setts.cellHeight();

    layers.push_back({});

    auto& map = layers[0];

    for (int y = 0; y < mapSize.y; ++y) {
      for (int x = 0; x < mapSize.x; ++x) {
        Entity::Type type = Entity::None;

        if (y == 0 || y == mapSize.y - 1 || x == 0 || x == mapSize.x - 1)
          type = Entity::Brick;

        map.emplace_back(type);
        map.back().left = x * setts.cellWidth();
        map.back().top = y * setts.cellHeight();
        map.back().width = setts.cellWidth();
        map.back().height = setts.cellHeight();
      }
    }
  }

  Entity& operator[](sf::Vector2i cell) {
    return layers[0][cell.y * mapSize.x + cell.x ];
  }

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    GameSettings& setts = GameSettings::instance();
    sf::RectangleShape block( sf::Vector2f(setts.cellWidth(), setts.cellHeight()) );

    for (const auto& layer : layers) {
      for (const auto& cell : layer) {
        sf::Color color;
        switch (cell.type) {
          case Entity::Brick:
            color = { 0, 0, 255 };
            break;
          case Entity::LightBrick:
            color = { 0, 0, 100 };
            break;
          case Entity::Enemy:
            color = { 255, 0, 0 };
            break;
          case Entity::Player:
            color = sf::Color::Green;
            break;
          case Entity::Destroy:
            color = sf::Color::Yellow;
            break;
          default:
            color = {0, 0, 0};
        }

        block.setPosition(cell.topLeft());
        block.setFillColor(color);

        target.draw(block);
      }
    }
  }

  using Layer = std::vector<Entity>;


  sf::Vector2i mapSize;
  std::vector<Layer> layers;
};

#endif // MAP_H
