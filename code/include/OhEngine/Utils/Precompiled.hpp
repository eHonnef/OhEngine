#pragma once

#define OHENGINE_PUBLIC __attribute__ ((visibility ("default")))
#define OHENGINE_PRIVATE __attribute__ ((visibility ("hidden")))

#include <OhEngine/Utils/Logger.hpp>
#include <OhEngine/Utils/Containers/Dictionary.hpp>
#include <OhEngine/Utils/Containers/List.hpp>
#include <OhEngine/Utils/Containers/Bimap.hpp>
//#include <string> #included from logger
//#include <vector> #included from list
#include <memory>
#include <functional>

