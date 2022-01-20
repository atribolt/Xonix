#include <thread>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Window.h"
#include "Logging/Log.h"
#include "GameSettings.h"

static Log wlog("Window");

Window::~Window()
{
}

Window& Window::instance()
{
  static Window window;
  return window;
}

void Window::init()
{
  _window = RenderWindowPtr(new sf::RenderWindow());
}

void Window::open()
{
  GameSettings& settings = GameSettings::instance();
  sf::VideoMode vMode(settings.windowWidth(), settings.windowHeight());

  _window->create(vMode, settings.windowTitle(),
                  sf::Style::None |
                  sf::Style::Titlebar |
                  sf::Style::Close);

  _window->setFramerateLimit(settings.maxFramerate());
}

void Window::close()
{
  _window->close();
}

bool Window::isOpen() const
{
  return _window->isOpen();
}

WindowPtr Window::getWindow()
{
  return _window;
}

RenderTargetPtr Window::getCanvas()
{
  return _window;
}

Window::Window()
{
}
