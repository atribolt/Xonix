#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>
#include <string>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Game.h"
#include "GameEvent.h"
#include "GameSettings.h"
#include "Interface/GameState.h"


class MenuState final : public GameState {
  enum Buttons {
    PlayOrContinue,
    Settings,
    Exit,

    Count
  };

public:
  MenuState()
    : GameState(Menu)
  {
    sf::Text text("", GameSettings::instance().font());
    text.setFillColor(sf::Color::White);

    button(PlayOrContinue) = (text.setString("Play"), text);
    button(Settings) = (text.setString("Settings"), text);
    button(Exit) = (text.setString("Exit"), text);
  }

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    for (const sf::Text& btn : _buttons) {
      target.draw(btn, states);
    }
  }
  void update() override {
    if (_updated)
      return;

    sf::Vector2f windowSize(
      GameSettings::instance().windowWidth(),
      GameSettings::instance().windowHeight()
    );

    float height = 0.f;

    for (sf::Text& btn : _buttons) {
      height += btn.getGlobalBounds().height;
    }

    float lastBtnBottom = (windowSize.y - height) / 2.f;
    for (sf::Text& btn : _buttons) {
      float top = lastBtnBottom;
      float left = (windowSize.x - btn.getGlobalBounds().width) / 2.f;
      btn.setPosition(left, top);

      lastBtnBottom += btn.getGlobalBounds().height;
    }

    _updated = true;
  }
  void handleEvent(const sf::Event& ev) override {
    if (ev.type == sf::Event::KeyReleased) {
      if (ev.key.code == sf::Keyboard::Escape) {
        GameEvent event;
        event.sender = this;

        if (_isPaused) {
          event.type = GameEvent::ResumeGame;
        }
        else {
          event.type = GameEvent::StartGame;
        }

        Game::instance().gameEvent(event);
      }
    }
    else if (ev.type == sf::Event::MouseButtonReleased) {
      sf::Text* changed {nullptr};

      for (sf::Text& btn : _buttons) {
        if (btn.getGlobalBounds().contains(ev.mouseButton.x, ev.mouseButton.y)) {
          changed = &btn;
          break;
        }
      }

      GameEvent event;
      event.sender = this;

      if (changed) {
        if (&button(PlayOrContinue) == changed) {
          if (_isPaused) {
            event.type = GameEvent::ResumeGame;
          }
          else {
            event.type = GameEvent::StartGame;
          }
        }
        else if (&button(Settings) == changed) {
          // TODO: do send open settings menu
        }
        else if (&button(Exit) == changed) {
          event.type = GameEvent::ExitGame;
        }

        Game::instance().gameEvent(event);
      }
    }
  }

  void onPause() {
    button(PlayOrContinue).setString("Continue");
    _updated = false;
    _isPaused = true;
  }
  void onDefault() {
    button(PlayOrContinue).setString("Play");
    _updated = false;
    _isPaused = false;
  }

private:
  sf::Text& button(Buttons btn) {
    return _buttons[btn];
  }

private:
  bool _updated {false};
  bool _isPaused {false};
  sf::Text _buttons[Count];
};

#endif // MENUSTATE_H
