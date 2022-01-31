#ifndef INPLAYSTATE_H
#define INPLAYSTATE_H

#include <SFML/Window/Event.hpp>

#include "Game.h"
#include "GameEvent.h"
#include "Interface/GameState.h"


class InPlayState final : public GameState {
public:
  InPlayState()
    : GameState(Played) {}

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

  }
  void update() override {

  }
  void handleEvent(const sf::Event& ev) override {
    if (ev.type == sf::Event::KeyReleased) {
      if (ev.key.code == sf::Keyboard::Escape) {
        GameEvent event;
        event.type = GameEvent::PauseGame;
        event.sender = this;

        Game::instance().gameEvent(event);
      }
    }
  }

  void reset() {}
  void pause() {}
  void resume() {}
  void play() {}
};

#endif // INPLAYSTATE_H
