/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

//#define OHENGINE_PUBLIC __attribute__ ((visibility ("default")))
//#define OHENGINE_PRIVATE __attribute__ ((visibility ("hidden")))
#define OHENGINE_PUBLIC
#define OHENGINE_PRIVATE

// Includes from the engine itself
#include <OhEngine/Utils/Containers/Bimap.hpp>
#include <OhEngine/Utils/Containers/Dictionary.hpp>
#include <OhEngine/Utils/Containers/List.hpp>
#include <OhEngine/Utils/Logger.hpp>

// 3rd party includes
#include <rapidobj/rapidobj.hpp>

// Includes from stdlib
//#include <string> #included from logger
//#include <vector> #included from list
#include <functional>
#include <memory>
