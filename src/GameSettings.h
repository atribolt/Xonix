#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <string>

class GameSettings {
public:
  static GameSettings& instance();

  bool loadConfig(const std::string& configPath);

  int windowWidth() const;
  int windowHeight() const;
  int maxFramerate() const;
  const std::string& windowTitle() const;

private:
  GameSettings();

  int _windowWidth;
  int _windowHeight;
  int _maxFramerate;
  std::string _windowTitle;
};

#endif // GAMESETTINGS_H
