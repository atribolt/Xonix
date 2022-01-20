#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <vector>

#include "Classes.h"


class ObjectFactory {
public:
  static ObjectFactory& instance();

  void init();

  GameObjectPtrList& getObjects();

private:
  ObjectFactory();

  GameObjectPtrList _objects;
};

#endif // OBJECTFACTORY_H
