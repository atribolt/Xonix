#include <thread>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Game.h"
#include "Logging/Log.h"
#include "GameSettings.h"
#include "Handlers/EventHandler.h"
#include "Handlers/CloseHandler.h"
#include "Handlers/PlayerController.h"
#include "Handlers/EnemyCollision.h"


static Log game("Game");


Game::Game()
{
  _window = nullptr;
  _exitRequest = false;
}

Game& Game::instance()
{
  static Game _instance;
  return _instance;
}

Game::~Game()
{
  exit();

  delete _window;

  for (EventHandler*& handler : _handlers) {
    delete handler;
  }
}

bool Game::loadConfig(const std::string& path)
{
  game.debug() << "Load config";
  bool status = GameSettings::instance().loadConfig(path);

  if (!status)
  {
    game.error() << "Error while load settings from" << path;
    return false;
  }

  game.debug() << "Config is loaded";
  return true;
}

void Game::init()
{
  game.debug() << "Init game";

  GameSettings& setts = GameSettings::instance();
  sf::VideoMode mode(setts.windowWidth(), setts.windowHeight());

  _engine.reset();
  _handlers.clear();
  _exitRequest = false;
  _map.init();

  _map.layers.push_back({});
  _map.layers.back().reserve(20);

  Entity& player = _map.layers.back().emplace_back(Entity::Player, 0.3f);

  srand(time(0));
  for (int i = 0; i < 10; ++i) {
    Entity* enemy = &(_map.layers.back().push_back({Entity::Enemy, 0.1f}), _map.layers.back().back());
    enemy->left = rand() % (setts.windowWidth() - setts.cellWidth() * 4) + setts.cellWidth() * 2;
    enemy->top = rand() % (setts.windowHeight() - setts.cellHeight() * 4) + setts.cellHeight() * 2;
    enemy->speed = rand() % 100 / 200.f;
    if (rand() % 4 > 2)
      enemy->setDirection(Entity::Right);
    else
      enemy->setDirection(Entity::Up);

    _engine.dinamycObjects.push_back(enemy);
  }

  for (auto& entity: _map.layers[0]) {
    _engine.staticObjects.push_back(&entity);
  }

  _engine.dinamycObjects.push_back(&player);
  _handlers.push_back(new CloseHandler);

  PlayerController* controller = new PlayerController(&player, &_map);
  _handlers.push_back(dynamic_cast<EventHandler*>(controller));
  _engine.handlers.push_back(dynamic_cast<CollisionHandler*>(controller));
  _engine.handlers.push_back(new EnemyCollision);

  _window = new sf::RenderWindow(mode, "Xonix", sf::Style::Close | sf::Style::Titlebar);
  _window->setFramerateLimit(setts.maxFramerate());
  _window->setVerticalSyncEnabled(true);
  _window->setPosition({0, 0});
}

void Game::start()
{
  game.debug() << "Start game";

  std::thread([this] () {
    GameSettings& setts = GameSettings::instance();

    while(_window->isOpen()) {
      _engine.step();
      std::this_thread::sleep_for(std::chrono::milliseconds(1000 / setts.maxFramerate()));
    }
  }).detach();

  using namespace std::chrono;
  GameSettings& setts = GameSettings::instance();

  _engine.start();

  while(_window->isOpen()) {
    sf::Event ev;
    while (_window->pollEvent(ev)) {
      for (EventHandler*& handler : _handlers) {
        handler->handle(ev);
      }
    }

    if (_exitRequest) {
      _window->close();
      break;
    }

    _window->clear();
    _window->draw(_map);
    _window->display();
  }
}

void Game::exit()
{
  game.debug() << "Exit game";
  _exitRequest = true;
}

void Game::restart()
{
  _window->close();

  delete _window;

  init();
  start();
}

void Game::gameOver()
{
  _engine.pause();

  for (Entity& cell : _map.layers[0])
    if (cell.type == Entity::LightBrick)
      cell.type = Entity::Destroy;
}
