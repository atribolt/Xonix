#ifndef LOG_H
#define LOG_H

#include <string>

class Log {
public:
  Log(std::string const& name);
  
  Log(Log&& other);
  Log&& operator=(Log&& other);
  
  Log(Log const& other);
  Log& operator=(Log const& other);
  
  ~Log();
  
  Log debug();
  Log warning();
  Log error();
  Log info();

private:
  enum LogLevel {
    Debug,
    Warning,
    Error,
    Info
  };
  
  Log(std::string const& name, LogLevel level);
  
  void swap(Log&& other);
  void swap(Log const& other);
  
  LogLevel _level;
  std::string _name;
  std::string _buffer;
  
  friend Log operator<< (Log log, std::string const& message);
};

Log operator<< (Log log, std::string const& message);


#define lDebug(log) log.debug()
#define lWarning(log) log.warning()
#define lError(log) log.error()
#define lInfo(log) log.info()

#endif // LOG_H
