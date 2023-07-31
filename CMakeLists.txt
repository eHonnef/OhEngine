# --------------------------------------------------------------------------------
# CMake configuration and safeguarding
# --------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)

# check if this is the main project
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(main_project ON)
  set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
  # Ask CMake to output a compile_commands.json file for use with things like
  # Vim.
  set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

  message(STATUS "Using toolchain: ${toolchain}")
  include(${toolchain})

  # Including other cmake modules
  include(Warnings)
  # include(Colors) # It is a little bugged, need rework
else()
  set(main_project OFF)
endif()

include(ConfigSafeGuards)

# --------------------------------------------------------------------------------
# General project settings
# --------------------------------------------------------------------------------
project(
  OhEngine # Project name
  VERSION 0.0.0.0 # Project version
  LANGUAGES CXX # Project language
)
set(namespace OhEngine)

# General C++ settings
set(CXX_STANDARD_REQUIRED ON) # Requires C++ standard
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)

# --------------------------------------------------------------------------------
# Enable/disable options
# --------------------------------------------------------------------------------
option(
  ENABLE_WARNINGS_SETTINGS
  "Allow target_set_warnings to add flags and defines.
                                 Set this to OFF if you want to provide your own warning parameters."
  ${main_project})
option(enable_lto "Enable link time optimization" OFF)
option(
  enable_tests
  "Include tests in the library. Setting this to OFF will remove all doctest related code."
  OFF)
option(enable_documentation "Enable the documentation build" OFF)

# --------------------------------------------------------------------------------
# General cmake includes
# --------------------------------------------------------------------------------
include(Documentation)
include(Misc)
include(LTO)

# Check for LTO support.
find_lto(CXX)

# --------------------------------------------------------------------------------
# Locate files
# --------------------------------------------------------------------------------
# Code location directory
set(code_dir ${CMAKE_CURRENT_LIST_DIR}/code)
# Where the source files are located
set(src_dir ${code_dir}/src)
# Where the headers files are located
set(include_dir ${code_dir}/include)

file(GLOB_RECURSE src_files CONFIGURE_DEPENDS "${src_dir}/*.cpp")
file(GLOB_RECURSE header_files CONFIGURE_DEPENDS "${include_dir}/*.hpp")

# --------------------------------------------------------------------------------
# Create code libraries
# --------------------------------------------------------------------------------
add_library(${PROJECT_NAME} OBJECT ${src_files})
add_library(${namespace}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${include_dir}>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

target_precompile_headers(${PROJECT_NAME} PUBLIC ${include_dir}/OhEngine/Utils/Precompiled.hpp)

include("${CMAKE_CURRENT_LIST_DIR}/thirdparty/thirdparty.cmake")
add_dependencies(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)

if(${cmake_build_type_tolower} STREQUAL "release" OR ${cmake_build_type_tolower}
                                                     STREQUAL "relwithdebinfo")
  target_enable_lto(${PROJECT_NAME} optimized)
endif()

if(${main_project})
  target_set_warnings(
    ${PROJECT_NAME}
    ENABLE
    ALL
    AS_ERROR
    ALL
    DISABLE
    Annoying)
endif()

# --------------------------------------------------------------------------------
# Main files target
# --------------------------------------------------------------------------------
if(${main_project})
  # Main files
  add_subdirectory(app)

  # Testings
  if(${enable_tests})
    message(STATUS "Tests are enabled")
    enable_testing()
    add_subdirectory(tests)
  endif()
endif()
