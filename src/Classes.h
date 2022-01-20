#ifndef CLASSES_H
#define CLASSES_H

#include <memory>
#include <vector>


class Animation;
using AnimationPtr = std::shared_ptr<Animation>;
using AnimationPtrList = std::vector<AnimationPtr>;

class GameObject;
using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectPtrList = std::vector<GameObjectPtr>;

class EventHandler;
using EventHandlerPtr = std::shared_ptr<EventHandler>;
using EventHandlerPtrList = std::vector<EventHandlerPtr>;

class Engine;
using EnginePtr = std::shared_ptr<Engine>;
using EnginePtrList = std::vector<EnginePtr>;

namespace sf {
  class Window;
  class Drawable;
  class RenderWindow;
  class RenderTarget;
}

using WindowPtr = sf::Window*;
using RenderWindowPtr = sf::RenderWindow*;
using RenderTargetPtr = sf::RenderTarget*;
using DrawableObjectPtr = std::shared_ptr<sf::Drawable>;
using DrawableObjectPtrList = std::vector<DrawableObjectPtr>;

#endif // CLASSES_H
