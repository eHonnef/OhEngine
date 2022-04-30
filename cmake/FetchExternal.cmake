# --------------------------------------------------------------------------------
#                                      FetchExternal <Change>
# --------------------------------------------------------------------------------
# Import all external libraries using FetchContent.
# --------------------------------------------------------------------------------
# Multi-Language Vulkan/GL/GLES/EGL/GLX/WGL Loader-Generator based on
# the official specs. http://glad.dav1d.de/
FetchContent_Declare(
  extern_glad
  
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.36
)
  
FetchContent_GetProperties(extern_glad)
if(NOT extern_glad_POPULATED)
  FetchContent_Populate(extern_glad)

  set(GLAD_INSTALL ON)
  add_subdirectory(
    ${extern_glad_SOURCE_DIR}
    ${extern_glad_BINARY_DIR}
    EXCLUDE_FROM_ALL
  )
endif()

# --------------------------------------------------------------------------------

FetchContent_Declare(fmtlib
  GIT_REPOSITORY "https://github.com/fmtlib/fmt"
  GIT_TAG "8.0.1"
  GIT_SHALLOW TRUE
)
set(FMT_INSTALL ON)
# --------------------------------------------------------------------------------
FetchContent_MakeAvailable(fmtlib)
list(APPEND lst_external fmt::fmt glad glfw)
