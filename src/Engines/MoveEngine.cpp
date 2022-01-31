#include "Engines/MoveEngine.h"


MoveEngine::MoveEngine() {

}

void MoveEngine::step() {
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

void MoveEngine::pause() {
  state = Stoped;
}

void MoveEngine::start() {
  state = Started;
  lastStep = ClockT::now();
}

void MoveEngine::reset() {
  state = Stoped;
  staticObjects.clear();
  dinamycObjects.clear();
  handlers.clear();
}
