#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

class PhysObject;

class CollisionHandler {
public:
  virtual ~CollisionHandler() {}
  virtual void onCollision(PhysObject* obj1, PhysObject* obj2) = 0;
  virtual void offCollision(PhysObject* obj1, PhysObject* obj2) = 0;
};

#endif // COLLISIONHANDLER_H
