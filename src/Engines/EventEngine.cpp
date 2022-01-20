#include <SFML/Window.hpp>

#include "Window.h"
#include "Classes.h"
#include "Engines/EventEngine.h"
#include "Engines/ObjectFactory.h"
#include "GameObjects/GameObject.h"
#include "EventHandlers/EventHandler.h"

EventEngine::EventEngine()
  : Engine("EventEngine")
{
}

void EventEngine::init()
{
  for (auto& gameObject : ObjectFactory::instance().getObjects()) {
    if (dynamic_cast<EventHandler*>(gameObject.get()) != nullptr) {
      EventHandlerPtr& handler = reinterpret_cast<EventHandlerPtr&>(gameObject);
      _handlers.push_back(handler);
    }
  }
}

void EventEngine::step(int)
{
  WindowPtr window = Window::instance().getWindow();

  if (window->isOpen())
  {
    sf::Event ev;

    while(window->pollEvent(ev)) {
      for (EventHandlerPtr& handler : _handlers) {
        handler->handle(ev);
      }
    }
  }
}
