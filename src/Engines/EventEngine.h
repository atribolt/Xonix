#ifndef EVENTENGINE_H
#define EVENTENGINE_H

#include "Classes.h"
#include "Engines/Engine.h"

class EventEngine final 
    : public Engine 
{
public:
  EventEngine();
  
  void init() override;
  
private:
  void step(int) override;
  
  EventHandlerPtrList _handlers;
};

#endif // EVENTENGINE_H
