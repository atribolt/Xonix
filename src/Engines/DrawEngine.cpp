#include <SFML/Graphics.hpp>

#include "Window.h"
#include "Engines/DrawEngine.h"
#include "Engines/ObjectFactory.h"
#include "GameObjects/GameObject.h"

DrawEngine::DrawEngine()
  : Engine("DrawEngine")
{
}

void DrawEngine::init()
{
  for (auto& gameObject : ObjectFactory::instance().getObjects()) {
    if (dynamic_cast<sf::Drawable*>(gameObject.get()) != nullptr) {
      DrawableObjectPtr& handler = reinterpret_cast<DrawableObjectPtr&>(gameObject);
      _drawables.push_back(handler);
    }
  }
}

void DrawEngine::step(int)
{
  RenderTargetPtr target = Window::instance().getCanvas();
  WindowPtr window =  Window::instance().getWindow();

  if (window->isOpen()) {
    target->clear();

    for (DrawableObjectPtr& obj : _drawables) {
      target->draw(*obj);
    }

    window->display();
  }
}
