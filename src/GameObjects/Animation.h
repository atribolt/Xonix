#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
  Animation();
  virtual ~Animation();

  virtual void update(int dTimeMs);

  void setSpeed(float speed);

private:
  float _speed;

};

#endif // ANIMATION_H
