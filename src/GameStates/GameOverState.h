#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Game.h"
#include "GameEvent.h"
#include "GameSettings.h"
#include "Interface/GameState.h"

class GameOverState final : public GameState {
public:
  GameOverState()
    : GameState(GameOver) {}

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    sf::Vector2u size = target.getSize();

    sf::Text text("Game Over\nYou score: " + std::to_string(_score), GameSettings::instance().font(), 30);
    sf::FloatRect bounds = text.getGlobalBounds();

    text.setPosition((size.x - bounds.width) / 2, (size.y - bounds.height) / 2);
    text.setFillColor(sf::Color::White);
    target.draw(text);
  }

  void update() override {}

  void handleEvent(const sf::Event& ev) override {
    if (ev.type == sf::Event::KeyReleased) {
      GameEvent event;
      event.type = GameEvent::GoToMenu;
      event.sender = this;
      Game::instance().gameEvent(event);
    }
  }

  void setScore(int score) {
    _score = score;
  }

private:
  int _score {0};
};

#endif // GAMEOVERSTATE_H
