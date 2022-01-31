#include "Interface/GameState.h"
#include "Logging/Log.h"

GameState::GameState(Type type)
  : _type(type) {}

GameState::~GameState() {}

GameState::Type GameState::type() const {
  return _type;
}


Log operator<<(Log log, GameState::Type type) {
  switch(type) {
    case GameState::Menu: log << "menu"; break;
    case GameState::Played: log << "played"; break;
    case GameState::GameOver: log << "game over"; break;
    default: log << "unknown"; break;
  }

  return log;
}
