#ifndef GMAE_H
#define GMAE_H


#include <string>
#include <vector>

#include "GameObjects/Map.h"
#include "Engines/MoveEngine.h"

namespace sf { class RenderWindow; }


class Game {
public:
  static Game& instance();
  ~Game();

  bool loadConfig(const std::string& path);
  void init();
  void start();
  void exit();

  void restart();
  void gameOver();

private:
  Game();

  bool _exitRequest;

  Map _map;
  MoveEngine _engine;
  sf::RenderWindow* _window;
  std::vector<class EventHandler*> _handlers;
};

#endif // GMAE_H
