#ifndef GMAE_H
#define GMAE_H


#include "Interface/GameState.h"

class GameEvent;

class Game final : public sf::Drawable {
private:
  Game();

public:
  ~Game();

  static Game& instance();

  bool isOpen() const;
  void event(sf::Event const& ev);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void gameEvent(const GameEvent& ev);
  void exit();

private:
  GameState*& state(GameState::Type state);

private:
  bool _exited {false};

  GameState* _currentState {nullptr};
  std::vector<GameState*> _states;
};

#endif // GMAE_H
