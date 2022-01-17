#ifndef LOGGER_H
#define LOGGER_H


#include <list>
#include <string>
#include <chrono>


enum class LogLevel {
  Debug,
  Warning,
  Error,
  Info
};


using Clock = std::chrono::high_resolution_clock;
using Time = Clock::time_point;

class LogImplement {
public:
  virtual void newMessage(std::string const& category,
                           Time time,
                           LogLevel level,
                           std::string const& msg);
};


class Logger {
public:
  static Logger& instance();

  LogImplement* init(LogImplement* impl);
  void setLevel(LogLevel level);

  void message(std::string const& name, std::string const& msg, 
               LogLevel level, Time time);
  void debug(std::string const& name, std::string const& msg);
  void warning(std::string const& name, std::string const& msg);
  void error(std::string const& name, std::string const& msg);
  void info(std::string const& name, std::string const& msg);
  
private:
  Logger();
  bool checkLevel(LogLevel level);

  LogLevel _filter;
};

#endif // LOGGER_H
