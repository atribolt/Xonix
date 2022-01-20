#include "Log.h"
#include "Logger.h"

Log::Log(const std::string& name)
  : _name(name)
{
}

Log::Log(Log&& other)
{
  swap(std::move(other));
}

Log&& Log::operator=(Log&& other)
{
  swap(std::move(other));
  return std::move(*this);
}

Log::Log(Log const& other)
{
  swap(other);
}

Log& Log::operator=(Log const& other)
{
  swap(other);
  return *this;
}

Log::~Log()
{
  if (_buffer.empty()) return;

  using Func = void (Logger::*)(std::string const&, std::string const&);
  Func writeLog;

  switch (_level) {
    case Log::Debug:
      Logger::instance().debug(_name, _buffer);
      //writeLog = &Logger::debug;
      break;
    case Log::Warning:
      Logger::instance().warning(_name, _buffer);
      //writeLog = &Logger::warning;
      break;
    case Log::Error:
      Logger::instance().error(_name, _buffer);
      //writeLog = &Logger::error;
      break;
    case Log::Info:
      Logger::instance().info(_name, _buffer);
      //writeLog = &Logger::info;
      break;
  }

  //(Logger::instance().*writeLog)(_name, _buffer);
}

Log Log::debug()
{
  return Log(_name, Debug);
}

Log Log::warning()
{
  return Log(_name, Warning);
}

Log Log::error()
{
  return Log(_name, Error);
}

Log Log::info()
{
  return Log(_name, Info);
}

Log::Log(const std::string& name, LogLevel level)
{
  _name = name;
  _level = level;
}

void Log::swap(Log&& other)
{
  std::swap(other._name, _name);
  std::swap(other._buffer, _buffer);
  std::swap(other._level, _level);
}

void Log::swap(const Log& other)
{
  std::swap(const_cast<Log&>(other)._name, _name);
  std::swap(const_cast<Log&>(other)._buffer, _buffer);
  std::swap(const_cast<Log&>(other)._level, _level);
}

Log operator<< (Log log, std::string const& message)
{
  log._buffer.append(" " + message);
  return log;
}
