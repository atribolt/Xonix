#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics/Drawable.hpp>

namespace sf {
  class Event;
}

class GameState : public sf::Drawable {
public:
  enum Type : char {
    Menu,
    Played,
    GameOver,

    Count
  };

  GameState(Type type);

  virtual ~GameState();

  Type type() const;
  virtual void update() = 0;
  virtual void handleEvent(sf::Event const& ev) = 0;

private:
  Type _type;
};

class Log operator<<(class Log, GameState::Type);

#endif // GAMESTATE_H
