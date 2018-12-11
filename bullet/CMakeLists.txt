
SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}" -D_DEBUG)

OPTION(USE_DOUBLE_PRECISION "Use double precision" OFF)
OPTION(BUILD_SHARED_LIBS "Use shared libraries" OFF)

add_subdirectory (src)