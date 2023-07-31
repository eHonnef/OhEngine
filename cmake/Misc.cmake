# --------------------------------------------------------------------------------
# Misc
# --------------------------------------------------------------------------------
# Have CMake parse the config file, generating the config header, with correct
# definitions. Here only used to make version number available to the source
# code. Include "Config.h" (no .in suffix) in the source.
configure_file("${CMAKE_CURRENT_LIST_DIR}/Config.hpp.in"
               "${CMAKE_CURRENT_BINARY_DIR}/Config.hpp")
# add the binary tree to the search path for include files so that we will find
# Config.h
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
