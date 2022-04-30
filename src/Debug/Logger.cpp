#include <OhEngine/Debug/Logger.h>
#include <iomanip>

Logger::Logger() : Thread() {
  std::stringstream strDateTime;
  auto time = std::time(nullptr);
  strDateTime << std::put_time(std::localtime(&time), "Logs_%Y-%m-%d");
}

Logger::~Logger() {
  stop();
}

void Logger::execute() {
  while (m_bIsRunning) {
  }
}

void Logger::info(const std::string &strLog) { enqueue(strLog); }

// void Logger::error(const std::string &strLog) {}
// void Logger::debug(const std::string &strLog) {}
// void Logger::warning(const std::string &strLog) {}
// void Logger::critical(const std::string &strLog) {}