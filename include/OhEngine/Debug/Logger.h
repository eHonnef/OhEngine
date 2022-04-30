#pragma once

#include <OhEngine/Utils/Thread.h>
#include <string>

class Logger : public Thread<std::string> {
protected:
  char m_arBuffer[4096];

  void execute();

public:
  Logger();
  ~Logger();

  void info(const std::string& strLog);
  // void error(const std::string& strLog);
  // void debug(const std::string& strLog);
  // void warning(const std::string& strLog);
  // void critical(const std::string& strLog);
};
