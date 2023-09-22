/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <cstddef>
#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>

namespace OhEngine {

    namespace LoggerConfig {
        enum ELogLevel { llTrace, llDebug, llInfo, llImportant, llWarning, llError, llCritical, llFatal, llNone };

        constexpr bool c_bEnableAllLogs = false;

#ifndef NDEBUG
        constexpr ELogLevel c_eLogLevel = ELogLevel::llTrace;
#else
        constexpr ELogLevel c_eLogLevel = ELogLevel::llNone;
#endif
    }  // namespace LoggerConfig

#define OHENGINE_TRACE(...)                                                                                            \
    if constexpr (c_bLogModule || LoggerConfig::c_bEnableAllLogs) {                                                    \
        Logger::Trace(__FILE__, __func__, __VA_ARGS__);                                                                \
    }
#define OHENGINE_DEBUG(...)                                                                                            \
    if constexpr (c_bLogModule || LoggerConfig::c_bEnableAllLogs) {                                                    \
        Logger::Debug(__FILE__, __func__, __VA_ARGS__);                                                                \
    }
#define OHENGINE_INFO(...)                                                                                             \
    if constexpr (c_bLogModule || LoggerConfig::c_bEnableAllLogs) {                                                    \
        Logger::Info(__FILE__, __func__, __VA_ARGS__);                                                                 \
    }
#define OHENGINE_IMPORTANT(...)                                                                                        \
    if constexpr (c_bLogModule || LoggerConfig::c_bEnableAllLogs) {                                                    \
        Logger::Important(__FILE__, __func__, __VA_ARGS__);                                                            \
    }
#define OHENGINE_WARNING(...)                                                                                          \
    if constexpr (c_bLogModule || LoggerConfig::c_bEnableAllLogs) {                                                    \
        Logger::Warning(__FILE__, __func__, __VA_ARGS__);                                                              \
    }
#define OHENGINE_ERROR(...) Logger::Error(__FILE__, __func__, __VA_ARGS__);
#define OHENGINE_CRITICAL(...) Logger::Critical(__FILE__, __func__, __VA_ARGS__);
#define OHENGINE_FATAL(...) Logger::Fatal(__FILE__, __func__, __VA_ARGS__);

    class OHENGINE_PRIVATE Logger {
    public:
        template<typename... Args>
        static void Trace(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                          const Args &...args) {
            Print<LoggerConfig::llTrace>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Debug(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                          const Args &...args) {
            Print<LoggerConfig::llDebug>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Info(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                         const Args &...args) {
            Print<LoggerConfig::llInfo>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Important(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                              const Args &...args) {
            Print<LoggerConfig::llImportant>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Warning(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                            const Args &...args) {
            Print<LoggerConfig::llWarning>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Error(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                          const Args &...args) {
            Print<LoggerConfig::llError>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Critical(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                             const Args &...args) {
            Print<LoggerConfig::llCritical>(strFileName, strFnName, str, args...);
        }

        template<typename... Args>
        static void Fatal(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                          const Args &...args) {
            Print<LoggerConfig::llFatal>(strFileName, strFnName, str, args...);
        }

    private:
        // if we later change to a thread (remove the static from the functions)
        // static Logger &GetInstance() {
        //     static Logger Instance{};
        //     return Instance;
        // }

        template<LoggerConfig::ELogLevel LL, typename... Args>
        static void Print(const std::string &strFileName, const std::string &strFnName, const std::string &str,
                          const Args &...args) {
            if constexpr (static_cast<size_t>(LL) >= static_cast<size_t>(LoggerConfig::c_eLogLevel)) {
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
            return fmt::format("{:%Y-%m-%d %H:%M:%S}", now);
        }

        template<LoggerConfig::ELogLevel LL>
        static std::string FormatMessage(const std::string &strFileName, const std::string &strFnName,
                                         const std::string_view &strMessage) {
            // Formatting each message as below:
            // Date Time.Ms [Level] :: File:FunctionName :: Message\n
            return fmt::format("{} {:<11} :: {} :: {}\r", GetTimeNow(), fmt::format("[{}]", LogLevelToString<LL>()),
                               fmt::format("{}:{}", strFileName, strFnName), strMessage);
        }

        template<LoggerConfig::ELogLevel LL>
        static constexpr fmt::text_style Color() {
            if constexpr (LL == LoggerConfig::llTrace) {
                return fmt::fg(fmt::color::light_gray);
            } else if constexpr (LL == LoggerConfig::llDebug) {
                return fmt::emphasis::bold | fmt::fg(fmt::color::dark_cyan);
            } else if constexpr (LL == LoggerConfig::llInfo) {
                return fmt::fg(fmt::color::white);
            } else if constexpr (LL == LoggerConfig::llImportant) {
                return fmt::fg(fmt::color::orange);
            } else if constexpr (LL == LoggerConfig::llWarning) {
                return fmt::emphasis::bold | fmt::fg(fmt::color::yellow);
            } else if constexpr (LL == LoggerConfig::llError) {
                return fmt::fg(fmt::color::red);
            } else if constexpr (LL == LoggerConfig::llCritical) {
                return fmt::emphasis::bold | fmt::bg(fmt::color::dark_red) | fmt::fg(fmt::color::white);
            } else if constexpr (LL == LoggerConfig::llFatal) {
                return fmt::emphasis::bold | fmt::bg(fmt::color::red) | fmt::fg(fmt::color::white);
            } else {
                return {};
            }
        }

        template<LoggerConfig::ELogLevel LL>
        static constexpr std::string LogLevelToString() {
            if constexpr (LL == LoggerConfig::llTrace) {
                return "TRACE";
            } else if constexpr (LL == LoggerConfig::llDebug) {
                return "DEBUG";
            } else if constexpr (LL == LoggerConfig::llInfo) {
                return "INFO";
            } else if constexpr (LL == LoggerConfig::llImportant) {
                return "IMPORTANT";
            } else if constexpr (LL == LoggerConfig::llWarning) {
                return "WARNING";
            } else if constexpr (LL == LoggerConfig::llError) {
                return "ERROR";
            } else if constexpr (LL == LoggerConfig::llCritical) {
                return "CRITICAL";
            } else if constexpr (LL == LoggerConfig::llFatal) {
                return "FATAL";
            } else if constexpr (LL == LoggerConfig::llNone) {
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
}  // namespace OhEngine
