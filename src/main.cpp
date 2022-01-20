#include "Logging/Log.h"
#include "Logging/Logger.h"

#include "Game.h"

static Log deflog("Main");

int main(int argc, char** argv) {
  Logger::instance().init(new LogImplement());
  Logger::instance().setLevel(LogLevel::Debug);

  Game& game = Game::instance();

  game.loadConfig("");
  game.init();
  game.start();

  return 0;
}
