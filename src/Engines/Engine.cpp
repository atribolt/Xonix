#include <chrono>
#include <thread>

#include "Logging/Log.h"
#include "GameSettings.h"
#include "Engines/Engine.h"

static Log engine("Engine");

Engine::Engine(const std::string& name)
  : _state(Stoped)
  , _name(name)
{
}

Engine::~Engine()
{
  if (isRunning())
    stop();
}

void Engine::syncStart()
{
  if (_state == Stoped) {
    engine.debug() << "syncStart engine:" << _name;
    engineLoop();
  }
}

void Engine::asyncStart()
{
  if (_state == Stoped) {
    engine.debug() << "asyncStart engine:" << _name;
    _thread = std::thread(&Engine::engineLoop, this);
    _thread.detach();
  }
}

void Engine::stop()
{
  engine.debug() << "Stoping engine:" << _name;
  _state = Stoping;

  if (_thread.joinable())
    _thread.join();
  engine.debug() << "Stoped engine:" << _name;
}

bool Engine::isRunning() const
{
  return _state == Started;
}

void Engine::engineLoop()
{
  _state = Started;
  using clock_t = std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;

  milliseconds msTime(1000 / GameSettings::instance().maxFramerate());

  auto last_step = clock_t::now();

  while (_state == Started) {
    auto upTime = clock_t::now();
    int dTimeMs = duration_cast<std::chrono::milliseconds>(upTime - last_step).count();
    step(dTimeMs);

    auto sleepTime = msTime - duration_cast<std::chrono::milliseconds>(upTime - clock_t::now());
    last_step = upTime;

    if (_state == Started)
      std::this_thread::sleep_for(sleepTime);
  }

  _state = Stoped;
}
