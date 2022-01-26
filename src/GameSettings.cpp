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

  this->_windowWidth = std::max(this->_windowWidth, 1900);
  this->_windowHeight = std::max(this->_windowHeight, 1000);
  this->_maxFramerate = std::max(this->_maxFramerate, 60);
  this->_windowTitle = "Xonix";

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
  return 10;
}

int GameSettings::cellHeight() const
{
  return 10;
}

const std::string& GameSettings::windowTitle() const
{
  return _windowTitle;
}

GameSettings::GameSettings()
{
}
