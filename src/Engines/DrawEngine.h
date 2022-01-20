#ifndef DRAWENGINE_H
#define DRAWENGINE_H

#include "Classes.h"
#include "Engines/Engine.h"

class DrawEngine final
    : public Engine
{
public:
  DrawEngine();

  void init() override;

private:
  void step(int) override;

  DrawableObjectPtrList _drawables;
};

#endif // DRAWENGINE_H
