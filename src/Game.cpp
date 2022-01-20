#include <thread>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Game.h"
#include "Window.h"
#include "Logging/Log.h"
#include "GameSettings.h"
#include "Engines/DrawEngine.h"
#include "Engines/EventEngine.h"
#include "Engines/AnimationEngine.h"
#include "Engines/ObjectFactory.h"

static Log game("Game");

Game::Game()
{
}

Game& Game::instance()
{
  static Game _instance;
  return _instance;
}

Game::~Game()
{
  exit();
}

bool Game::loadConfig(const std::string& path)
{
  game.debug() << "Load config...";
  bool status = GameSettings::instance().loadConfig(path);

  if (!status)
  {
    game.error() << "Error while load settings from" << path;
    return false;
  }

  game.debug() << "Config is loaded...";
  return true;
}

void Game::init()
{
  game.debug() << "Init game...";
  Window::instance().init();
  ObjectFactory::instance().init();

  _engines.push_back(EnginePtr(new EventEngine()));
  _engines.push_back(EnginePtr(new DrawEngine()));
  _engines.push_back(EnginePtr(new AnimationEngine()));

  for (EnginePtr& engine : _engines) {
    engine->init();
  }
}

void Game::start()
{
  game.debug() << "Start game...";
  Window::instance().open();

  for (int i = 0; i < _engines.size() - 1; ++i) {
    _engines[i]->asyncStart();
  }

  _engines.back()->syncStart();
}

void Game::exit()
{
  game.debug() << "Stoping all engines";

  for (auto iter = _engines.rbegin(); iter != _engines.rend(); ++iter) {
    (*iter)->stop();
  }

  game.debug() << "Wait for finished engines";
  bool allStoped = false;
  while (!allStoped) {
    bool anyRunning = false;
    for (EnginePtr& engine : _engines) {
      anyRunning |= engine->isRunning();
    }

    allStoped = !anyRunning;
  }

  Window::instance().close();
}
