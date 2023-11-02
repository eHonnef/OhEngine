/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <Logger/Logger.hpp>

namespace OhEngine {

    namespace LoggerConfig {

        constexpr bool c_bEnableAllLogs = false;

#ifndef NDEBUG
        constexpr eho::LogLevel c_eLogLevel = eho::LogLevel::Trace;
#else
        constexpr eho::LogLevel c_eLogLevel = eho::LogLevel::None;
#endif
    }  // namespace LoggerConfig

    using Logger = eho::CLogger<LoggerConfig::c_eLogLevel>;
}  // namespace OhEngine
