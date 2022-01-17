#include <iostream>
#include <ctime>
#include <mutex>
#include <thread>

#include "Logger.h"


static std::mutex log_mutex;
static std::thread log_thread;
static LogImplement* implement;


void LogImplement::newMessage(const std::string& category, Time time, LogLevel level, const std::string& msg)
{
  std::string str_level;

  switch(level)
  {
    case LogLevel::Debug:
      str_level = "DEBUG";
      break;
    case LogLevel::Warning:
      str_level = "WARNING";
      break;
    case LogLevel::Error:
      str_level = "ERROR";
      break;
    case LogLevel::Info:
      str_level = "INFO";
      break;
  }

  std::cout << time.time_since_epoch().count() << " [" << str_level << "] {" << category << "} " << msg << '\n';
}

Logger& Logger::instance()
{
  static Logger logger;
  return logger;
}

LogImplement* Logger::init(LogImplement* impl)
{
  LogImplement* old = implement;
  implement = impl;
  return old;
}

void Logger::setLevel(LogLevel level)
{
  _filter = level;
}

void Logger::message(const std::string& name, const std::string& msg, 
                     LogLevel level, Time time)
{
  if (checkLevel(level) && implement) {
    std::lock_guard lock(log_mutex);
    implement->newMessage(name, time, level, msg);
  }
}

void Logger::debug(std::string const& name, const std::string& msg)
{
  message(name, msg, LogLevel::Debug, Clock::now());
}

void Logger::warning(std::string const& name, const std::string& msg)
{
  message(name, msg, LogLevel::Warning, Clock::now());
}

void Logger::error(std::string const& name, const std::string& msg)
{
  message(name, msg, LogLevel::Error, Clock::now());
}

void Logger::info(std::string const& name, const std::string& msg)
{
  message(name, msg, LogLevel::Info, Clock::now());
}

Logger::Logger()
{
}

bool Logger::checkLevel(LogLevel level)
{
  return _filter <= level;
}
