#ifndef ANIMATIONENGINE_H
#define ANIMATIONENGINE_H

#include "Classes.h"
#include "Engines/Engine.h"

class AnimationEngine final : public Engine {
public:
  AnimationEngine();
  
  void init() override;
  
private:
  void step(int dTimeMs) override;
  
  AnimationPtrList _animations;
};

#endif // ANIMATIONENGINE_H
