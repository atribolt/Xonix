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

  MoveEngine(){}

  void step() {
    if (state == Stoped) return;

    using namespace std::chrono;

    GameSettings& setts = GameSettings::instance();
    int dt = duration_cast<milliseconds>(ClockT::now() - lastStep).count();
    lastStep = ClockT::now();

    if (state == Paused) return;

    // move objects
    for (int i = 0; i < dinamycObjects.size(); ++i) {
      PhysObject* obj = dinamycObjects[i];
      obj->move(obj->direction * obj->speed * float(dt));
    }

    // find and send signal onCollision and offCollision
    for (int i = 0; i < dinamycObjects.size(); ++i) {
      PhysObject* obj1 = dinamycObjects[i];

      for (int j = i; j < staticObjects.size(); ++j) {
        PhysObject* obj2 = staticObjects[j];

        if (obj2->contains(obj1->center())) {
          for(int h = 0; h < handlers.size(); ++h) {
            handlers[h]->onCollision(obj1, obj2);
          }
        }
      }
      for (int j = i + 1; j < dinamycObjects.size() - 1; ++j) {
        PhysObject* obj2 = dinamycObjects[j];

        if (obj2->contains(obj1->center())) {
          for(int h = 0; h < handlers.size(); ++h) {
            handlers[h]->onCollision(obj1, obj2);
          }
        }
      }
    }
  }

  void pause() {
    state = Stoped;
  }
  void start() {
    state = Started;
    lastStep = ClockT::now();
  }

  void reset() {
    state = Stoped;
    staticObjects.clear();
    dinamycObjects.clear();
    handlers.clear();
  }



  State state;
  std::vector<PhysObject*> staticObjects;
  std::vector<PhysObject*> dinamycObjects;
  std::vector<CollisionHandler*> handlers;
  ClockT::time_point lastStep { ClockT::now() };
};

#endif // MOVEENGINE_H
