#ifndef GMAE_H
#define GMAE_H

#include <string>
#include "Classes.h"

class Game {
public:
  static Game& instance();
  ~Game();

  bool loadConfig(const std::string& path);
  void init();
  void start();
  void exit();

private:
  Game();

  EnginePtrList _engines;
};

#endif // GMAE_H
