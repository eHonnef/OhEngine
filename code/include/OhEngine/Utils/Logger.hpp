#pragma once

#include <cstddef>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>

namespace OhEngine {

#define LOGLEVEL 0

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define TRACE(...) Logger::Trace(__FILENAME__, __func__, __VA_ARGS__)
#define DEBUG(...) Logger::Debug(__FILENAME__, __func__, __VA_ARGS__)
#define INFO(...) Logger::Info(__FILENAME__, __func__, __VA_ARGS__)
#define IMPORTANT(...) Logger::Important(__FILENAME__, __func__, __VA_ARGS__)
#define WARNING(...) Logger::Warning(__FILENAME__, __func__, __VA_ARGS__)
#define ERROR(...) Logger::Error(__FILENAME__, __func__, __VA_ARGS__)
#define CRITICAL(...) Logger::Critical(__FILENAME__, __func__, __VA_ARGS__)
#define FATAL(...) Logger::Fatal(__FILENAME__, __func__, __VA_ARGS__)

class Logger {
  public:
    template <typename... Args>
    static void Trace(const std::string &strFileName, const std::string &strFnName, const std::string &str, const Args &...args) {
        Print(llTrace, strFileName, strFnName, str, args...);
    }
    template <typename... Args> static void Debug(const std::string &str, const Args &...args) { Print(llDebug, str, args...); }
    template <typename... Args> static void Info(const std::string &str, const Args &...args) { Print(llInfo, str, args...); }
    template <typename... Args> static void Important(const std::string &str, const Args &...args) { Print(llImportant, str, args...); }
    template <typename... Args> static void Warning(const std::string &str, const Args &...args) { Print(llWarning, str, args...); }
    template <typename... Args> static void Error(const std::string &str, const Args &...args) { Print(llError, str, args...); }
    template <typename... Args> static void Critical(const std::string &str, const Args &...args) { Print(llCritical, str, args...); }
    template <typename... Args> static void Fatal(const std::string &str, const Args &...args) { Print(llFatal, str, args...); }

  private:
    enum ELogLevel { llTrace, llDebug, llInfo, llImportant, llWarning, llError, llCritical, llFatal, llNone };

    // if we later change to a thread (remove the static from the functions)
    // static Logger &GetInstance() {
    //     static Logger Instance{};
    //     return Instance;
    // }

    template <typename... Args>
    static void Print(ELogLevel LL, const std::string &strFileName, const std::string &strFnName, const std::string &str,
                      const Args &...args) {
        if (static_cast<size_t>(LL) >= LOGLEVEL) {
            fmt::print(Color(LL),
                       FormatMessage(LL, strFileName, strFnName, fmt::vformat(str, fmt::format_args(fmt::make_format_args(args...)))));
        }
    }

    static std::string GetTimeNow() {
        using namespace std::chrono;
        std::chrono::sys_time<nanoseconds> now = (std::chrono::system_clock::now());
        auto round_now = std::chrono::round<milliseconds>(now);
        auto ms = (round_now.time_since_epoch() % seconds(1)).count();
        return fmt::format("{:%Y-%m-%d %H:%M:%S}.{:04}", now, ms);
    }

    static std::string FormatMessage(ELogLevel LogLevel, const std::string &strFileName, const std::string &strFnName,
                                     const std::string_view &strMessage) {
        // Formatting each message as below:
        // Date Time.Ms [Level] :: File:FunctionName :: Message\n
        return fmt::format("{} {:<11} :: {} :: {}\r\n", GetTimeNow(), fmt::format("[{}]", LogLevelToString(LogLevel)),
                           fmt::format("{}:{}", strFileName, strFnName), strMessage);
    }

    static fmt::text_style Color(ELogLevel LL) {
        switch (LL) {
        case llTrace:
            return fmt::fg(fmt::color::light_gray);
        case llDebug:
            return fmt::emphasis::bold | fmt::fg(fmt::color::dark_cyan);
        case llInfo:
            return fmt::fg(fmt::color::white);
        case llImportant:
            return fmt::fg(fmt::color::orange);
        case llWarning:
            return fmt::emphasis::bold | fmt::fg(fmt::color::yellow);
        case llError:
            return fmt::fg(fmt::color::red);
        case llCritical:
            return fmt::emphasis::bold | fmt::bg(fmt::color::dark_red) | fmt::fg(fmt::color::white);
        case llFatal:
            return fmt::emphasis::bold | fmt::bg(fmt::color::red) | fmt::fg(fmt::color::white);
        case llNone:
            return fmt::text_style();
        }
        return fmt::text_style();
    }

    static std::string LogLevelToString(ELogLevel LogLevel) {
        switch (LogLevel) {
        case llTrace:
            return "TRACE";
        case llDebug:
            return "DEBUG";
        case llInfo:
            return "INFO";
        case llImportant:
            return "IMPORTANT";
        case llWarning:
            return "WARNING";
        case llError:
            return "ERROR";
        case llCritical:
            return "CRITICAL";
        case llFatal:
            return "FATAL";
        case llNone:
            return "NONE";
        }
        return "";
    }

    Logger() {}

  public:
    Logger(Logger const &) = delete;
    void operator=(Logger const &) = delete;
};
}; // namespace OhEngine
