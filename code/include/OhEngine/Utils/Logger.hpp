#pragma once

#include <cstddef>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>

namespace OhEngine {
#define ENABLE_ALL_LOGS 0
#define LOGLEVEL 0

#define TRACE(...)                                                                                                     \
    if constexpr (LOG_MODULE) {                                                                                        \
        Logger::Trace(__FILE__, __func__, __VA_ARGS__);                                                                \
    }
#define DEBUG(...)                                                                                                     \
    if constexpr (LOG_MODULE) {                                                                                        \
        Logger::Debug(__FILE__, __func__, __VA_ARGS__);                                                                \
    }
#define INFO(...)                                                                                                      \
    if constexpr (LOG_MODULE) {                                                                                        \
        Logger::Info(__FILE__, __func__, __VA_ARGS__);                                                                 \
    }
#define IMPORTANT(...)                                                                                                 \
    if constexpr (LOG_MODULE) {                                                                                        \
        Logger::Important(__FILE__, __func__, __VA_ARGS__);                                                            \
    }
#define WARNING(...)                                                                                                   \
    if constexpr (LOG_MODULE) {                                                                                        \
        Logger::Warning(__FILE__, __func__, __VA_ARGS__);                                                              \
    }
#define ERROR(...)                                                                                                     \
    if constexpr (LOG_MODULE) {                                                                                        \
        Logger::Error(__FILE__, __func__, __VA_ARGS__);                                                                \
    }
#define CRITICAL(...)                                                                                                  \
    if constexpr (LOG_MODULE) {                                                                                        \
        Logger::Critical(__FILE__, __func__, __VA_ARGS__);                                                             \
    }
#define FATAL(...)                                                                                                     \
    if constexpr (LOG_MODULE) {                                                                                        \
        Logger::Fatal(__FILE__, __func__, __VA_ARGS__);                                                                \
    }

    class Logger {
    public:
        template<typename... Args>
        static void Trace(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                          const Args &...args) {
            Print<llTrace>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Debug(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                          const Args &...args) {
            Print<llDebug>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Info(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                         const Args &...args) {
            Print<llInfo>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Important(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                              const Args &...args) {
            Print<llImportant>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Warning(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                            const Args &...args) {
            Print<llWarning>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Error(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                          const Args &...args) {
            Print<llError>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Critical(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                             const Args &...args) {
            Print<llCritical>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Fatal(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                          const Args &...args) {
            Print<llFatal>(strFileName, strFnName, str, args...);
        }

    private:
        enum ELogLevel { llTrace, llDebug, llInfo, llImportant, llWarning, llError, llCritical, llFatal, llNone };

        // if we later change to a thread (remove the static from the functions)
        // static Logger &GetInstance() {
        //     static Logger Instance{};
        //     return Instance;
        // }

        template<ELogLevel LL, typename... Args>
        static void Print(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                          const Args &...args) {
            if constexpr (static_cast<size_t>(LL) >= LOGLEVEL) {
                fmt::print(Color<LL>(),
                           FormatMessage<LL>(
                             strFileName.substr(strFileName.find_last_of('/', std::string::npos) == std::string::npos
                                                  ? 0
                                                  : strFileName.find_last_of('/', std::string::npos) + 1),
                             strFnName, fmt::vformat(str, fmt::format_args(fmt::make_format_args(args...)))));
            }
        }

        static std::string GetTimeNow() {
            using namespace std::chrono;
            std::chrono::sys_time<nanoseconds> now = (std::chrono::system_clock::now());
            auto round_now = std::chrono::round<milliseconds>(now);
            auto ms = (round_now.time_since_epoch() % seconds(1)).count();
            return fmt::format("{:%Y-%m-%d %H:%M:%S}.{:04}", now, ms);
        }

        template<ELogLevel LL>
        static std::string FormatMessage(const std::string &strFileName, const std::string &strFnName,
                                         const std::string_view &strMessage) {
            // Formatting each message as below:
            // Date Time.Ms [Level] :: File:FunctionName :: Message\n
            return fmt::format("{} {:<11} :: {} :: {}\r", GetTimeNow(), fmt::format("[{}]", LogLevelToString<LL>()),
                               fmt::format("{}:{}", strFileName, strFnName), strMessage);
        }

        template<ELogLevel LL>
        static constexpr fmt::text_style Color() {
            if constexpr (LL == llTrace) {
                return fmt::fg(fmt::color::light_gray);
            } else if constexpr (LL == llDebug) {
                return fmt::emphasis::bold | fmt::fg(fmt::color::dark_cyan);
            } else if constexpr (LL == llInfo) {
                return fmt::fg(fmt::color::white);
            } else if constexpr (LL == llImportant) {
                return fmt::fg(fmt::color::orange);
            } else if constexpr (LL == llWarning) {
                return fmt::emphasis::bold | fmt::fg(fmt::color::yellow);
            } else if constexpr (LL == llError) {
                return fmt::fg(fmt::color::red);
            } else if constexpr (LL == llCritical) {
                return fmt::emphasis::bold | fmt::bg(fmt::color::dark_red) | fmt::fg(fmt::color::white);
            } else if constexpr (LL == llFatal) {
                return fmt::emphasis::bold | fmt::bg(fmt::color::red) | fmt::fg(fmt::color::white);
            } else {
                return {};
            }
        }

        template<ELogLevel LL>
        static constexpr std::string LogLevelToString() {
            if constexpr (LL == llTrace) {
                return "TRACE";
            } else if constexpr (LL == llDebug) {
                return "DEBUG";
            } else if constexpr (LL == llInfo) {
                return "INFO";
            } else if constexpr (LL == llImportant) {
                return "IMPORTANT";
            } else if constexpr (LL == llWarning) {
                return "WARNING";
            } else if constexpr (LL == llError) {
                return "ERROR";
            } else if constexpr (LL == llCritical) {
                return "CRITICAL";
            } else if constexpr (LL == llFatal) {
                return "FATAL";
            } else if constexpr (LL == llNone) {
                return "NONE";
            } else {
                return "";
            }
        }

        Logger() = default;

    public:
        Logger(Logger const &) = delete;
        void operator=(Logger const &) = delete;
    };
}// namespace OhEngine
