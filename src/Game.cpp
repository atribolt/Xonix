#include <string>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Logging/Log.h"
#include "GameSettings.h"

#include "GameEvent.h"
#include "GameStates/MenuState.h"
#include "GameStates/InPlayState.h"
#include "GameStates/GameOverState.h"


static Log game("Game");


Game::Game() {
  game.debug() << __FUNCTION__;
  GameSettings::instance().loadConfig("");

  _states.resize(GameState::Count);

  state(GameState::Menu) = new MenuState;
  state(GameState::Played) = new InPlayState;
  state(GameState::GameOver) = new GameOverState;

  _currentState = state(GameState::Menu);
}

Game::~Game() {
  game.debug() << __FUNCTION__;

  for (GameState* s : _states) {
    delete s;
  }
}

Game& Game::instance() {
  static Game _instance;
  return _instance;
}

bool Game::isOpen() const {
  return !_exited;
}

void Game::event(const sf::Event& ev) {
  _currentState->handleEvent(ev);
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  _currentState->update();
  target.draw(*_currentState);
}

void Game::gameEvent(const GameEvent& ev) {
  switch (ev.type) {
    case GameEvent::StartGame:
    case GameEvent::RestartGame: {
      InPlayState* tmp = dynamic_cast<InPlayState*>(state(GameState::Played));
      tmp->reset();
      tmp->play();
      _currentState = tmp;
      break;
    }
    case GameEvent::ResumeGame: {
      InPlayState* tmp = dynamic_cast<InPlayState*>(state(GameState::Played));
      tmp->resume();
      _currentState = tmp;
      break;
    }
    case GameEvent::PauseGame: {
      MenuState* tmpMenu = dynamic_cast<MenuState*>(state(GameState::Menu));
      ev.playState->pause();
      tmpMenu->onPause();
      _currentState = tmpMenu;
      break;
    }
    case GameEvent::GameOver: {
      GameOverState* tmp = dynamic_cast<GameOverState*>(state(GameState::GameOver));
      tmp->setScore(ev.results.score);
      break;
    }
    case GameEvent::GoToMenu: {
      MenuState* tmpMenu = dynamic_cast<MenuState*>(state(GameState::Menu));
      tmpMenu->onDefault();
      _currentState = tmpMenu;
      break;
    }
    case GameEvent::ExitGame: {
      this->exit();
    }
  }
}

void Game::exit() {
  _exited = true;
}

GameState*& Game::state(GameState::Type state) {
  return _states[state];
}
