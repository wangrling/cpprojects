cmake_minimum_required (VERSION 3.8)

project (Cpprojects)

# The version number
set (CPPROJECTS_VERSION_MAJOR 1)
set (CPPROJECTS_VERSION_MINOR 0)

# Configure a header file to pass some of the CMake settings
# to the source code.
configure_file(
    "${PROJECT_SOURCE_DIR}/Config.h.in"
    "${PROJECT_BINARY_DIR}/Config.h")


option (DEBUG "debug" ON)

include_directories ("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/include/")
include_directories ("${PROJECT_SOURCE_DIR}/include/flac/")

add_subdirectory (src/opengl)
add_subdirectory (src/boost)
add_subdirectory (src/flac)

add_subdirectory (filament)