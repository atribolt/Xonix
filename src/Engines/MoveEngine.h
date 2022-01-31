#ifndef MOVEENGINE_H
#define MOVEENGINE_H

#include <vector>
#include <chrono>
#include <SFML/Graphics/Shape.hpp>

#include "GameObjects/PhysObjects.h"
#include "Handlers/CollisionHandler.h"
#include "GameSettings.h"

using ClockT = std::chrono::high_resolution_clock;

class MoveEngine {
public:
  enum State {
    Paused,
    Started,
    Stoped
  };

  MoveEngine();

  void step();
  void pause();
  void start();
  void reset();
  State state() const;

  template<class Handler>
    void addHandler(Handler* handler);

  template<class Object, class ...Args>
    Object* registerObject(Args&&... args);


private:
  State _state;
  std::vector<PhysObject*> staticObjects;
  std::vector<PhysObject*> dinamycObjects;
  std::vector<CollisionHandler*> handlers;

  ClockT::time_point lastStep { ClockT::now() };
};

#endif // MOVEENGINE_H
