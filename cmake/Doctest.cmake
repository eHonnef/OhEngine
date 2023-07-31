include(CTest)
include(FetchContent)
add_definitions(-DENABLE_DOCTEST_IN_LIBRARY)

FetchContent_Declare(
  DocTest
  GIT_REPOSITORY "https://github.com/onqtam/doctest"
  GIT_SHALLOW TRUE
  GIT_TAG "v2.4.8"
  # EXCLUDE_FROM_ALL TRUE # doesn't work. check
  # https://gitlab.kitware.com/cmake/cmake/-/issues/20167
)
# FetchContent_MakeAvailable(DocTest)

if(NOT doctest_POPULATED)
  message(STATUS "Cloning DocTest")
  FetchContent_Populate(DocTest)
  add_subdirectory(${doctest_SOURCE_DIR} ${doctest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
