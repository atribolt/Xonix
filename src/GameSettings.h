#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <string>
#include <SFML/Graphics/Font.hpp>

class GameSettings {
public:
  static GameSettings& instance();

  bool loadConfig(const std::string& configPath);

  int windowWidth() const;
  int windowHeight() const;
  int maxFramerate() const;
  int cellWidth() const;
  int cellHeight() const;
  const sf::Font& font() const;
  const std::string& windowTitle() const;

private:
  GameSettings();

  int _windowWidth;
  int _windowHeight;
  int _maxFramerate;
  int _cellWidth;
  int _cellHeight;
  sf::Font _font;
  std::string _windowTitle;
};

#endif // GAMESETTINGS_H
