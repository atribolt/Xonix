#include <SFML/Graphics/Drawable.hpp>

#include "GameObjects/Animation.h"
#include "Engines/ObjectFactory.h"
#include "GameObjects/GameObject.h"
#include "Engines/AnimationEngine.h"


AnimationEngine::AnimationEngine()
  : Engine("AnimationEngine")
{
}

void AnimationEngine::init()
{
  for (auto& gameObject : ObjectFactory::instance().getObjects()) {
    if (dynamic_cast<sf::Drawable*>(gameObject.get()) != nullptr) {
      AnimationPtr& handler = reinterpret_cast<AnimationPtr&>(gameObject);
      _animations.push_back(handler);
    }
  }
}

void AnimationEngine::step(int dTimeMs)
{
  for (AnimationPtr& anim : _animations) {
    anim->update(dTimeMs);
  }
}
