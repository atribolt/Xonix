#include "Engines/ObjectFactory.h"
#include "EventHandlers/ExitGame.h"


ObjectFactory& ObjectFactory::instance()
{
  static ObjectFactory factory;
  return factory;
}

void ObjectFactory::init()
{
  _objects.push_back(EventHandlerPtr(new ExitGame));
}

GameObjectPtrList& ObjectFactory::getObjects()
{
  return _objects;
}

ObjectFactory::ObjectFactory()
{
}
