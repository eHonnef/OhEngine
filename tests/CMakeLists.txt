cmake_minimum_required(VERSION 3.25)

include(Doctest)

# List all files containing tests.
file(GLOB_RECURSE test_src_files CONFIGURE_DEPENDS "*.cpp")

set(TEST_MAIN unit_tests) # Default name for test executable
set(TEST_RUNNER_PARAMS "") # Any arguments to feed the test runner

# --------------------------------------------------------------------------------
# Make Tests
# --------------------------------------------------------------------------------
add_executable(${TEST_MAIN} ${test_src_files})
add_dependencies(${TEST_MAIN} ${namespace}::${PROJECT_NAME})
target_link_libraries(${TEST_MAIN} PRIVATE ${namespace}::${PROJECT_NAME}
                                           doctest)
set_target_properties(${TEST_MAIN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                              ${PROJECT_BINARY_DIR})
target_set_warnings(
  ${TEST_MAIN}
  ENABLE
  ALL
  AS_ERROR
  ALL
  DISABLE
  Annoying) # Set warnings (if needed).

add_test(
  # Use some per-module/project prefix so that it is easier to run only tests
  # for this module
  NAME ${PROJECT_NAME}.${TEST_MAIN} COMMAND ${TEST_MAIN} ${TEST_RUNNER_PARAMS})

# Adds a 'coverage' target.
include(CodeCoverage)
