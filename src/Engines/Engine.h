#ifndef ENGINE_H
#define ENGINE_H

#include <thread>
#include <string>

class Engine {
public:
  enum State : char {
    Started,
    Stoping,
    Stoped
  };

  Engine(const std::string& name);
  virtual ~Engine();

  virtual void init() {};

  void syncStart();
  void asyncStart();
  void stop();

  bool isRunning() const;

protected:
  virtual void step(int dTimeMs) {};

private:
  void engineLoop();

  State _state;
  std::string _name;
  std::thread _thread;
};

#endif // ENGINE_H
