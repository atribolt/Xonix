#include <map>
#include <fstream>
#include <algorithm>

#include "GameSettings.h"
#include "Logging/Log.h"

static Log setts("Settings");

static void strip(std::string_view& str) {
  int begin = str.find_first_not_of(' ');
  int end = str.find_last_not_of(' ');

  str.remove_suffix(str.size() - end);
  str.remove_prefix(begin);
}

GameSettings& GameSettings::instance()
{
  static GameSettings settings;
  return settings;
}

bool GameSettings::loadConfig(const std::string& configPath)
{
  std::map<std::string_view, std::function<void(std::string_view)>> opers {
    { "WindowWidth", [this](std::string_view str) {
      this->_windowWidth = std::stoi(str.data());
    }},
    { "WindowHeight", [this](std::string_view str) {
      this->_windowHeight = std::stoi(str.data());
    }},
    { "MaxFramerate", [this](std::string_view str) {
      this->_maxFramerate = std::stoi(str.data());
    }}
  };

  setts.debug() << "Load config from" << configPath;

  std::ifstream config(configPath);
  if (config)
  {
    std::string line;
    while(std::getline(config, line)) {
      if (line.size() > 0 && line[0] != '#') {
        int name_len = line.find('=');
        int value_len = line.size() - name_len - 1;

        if (name_len != -1) {
          std::string_view name(line.data(), name_len);
          std::string_view value(line.data() + name_len + 1, value_len);

          strip(name);
          strip(value);

          auto function = opers.find(name);
          if (function != opers.end())
            function->second(value);
        }
      }
    }
  }

  this->_windowWidth = std::max(this->_windowWidth, 640);
  this->_windowHeight = std::max(this->_windowHeight, 420);
  this->_maxFramerate = std::max(this->_maxFramerate, 30);
  this->_windowTitle = "Xonix";
  this->_cellWidth = 10;
  this->_cellHeight = 10;
  this->_font.loadFromFile("font.ttf");

  return true;
}

int GameSettings::windowWidth() const
{
  return _windowWidth;
}

int GameSettings::windowHeight() const
{
  return _windowHeight;
}

int GameSettings::maxFramerate() const
{
  return _maxFramerate;
}

int GameSettings::cellWidth() const
{
  return _cellWidth;
}

int GameSettings::cellHeight() const
{
  return _cellHeight;
}

const sf::Font& GameSettings::font() const
{
  return _font;
}

const std::string& GameSettings::windowTitle() const
{
  return _windowTitle;
}

GameSettings::GameSettings()
{
}
