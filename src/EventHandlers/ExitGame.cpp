#include "Game.h"
#include "EventHandlers/ExitGame.h"

ExitGame::ExitGame()
{
}

void ExitGame::handle(const sf::Event& event)
{
  if (event.type == sf::Event::Closed)
  {
    Game::instance().exit();
  }
}
