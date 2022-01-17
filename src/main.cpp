#include "Logger.h"
#include "Log.h"

static Log deflog("Main");

int main(int argc, char** argv) {
  Logger::instance().init(new LogImplement());
  Logger::instance().setLevel(LogLevel::Debug);

  lDebug(deflog) << "Project log init";
  
  return 0;
}
