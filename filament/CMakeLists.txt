

# ===================================================
# OS specific
# ===================================================
if (UNIX AND NOT APPLE AND NOT ANDROID AND NOT WEBGL)
    set(LINUX TRUE)
endif();

# ===================================================
# Paths
# ===================================================
# Where our external libs are
set (EXTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

# Where our libraries are
set (LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# Where our filament code is
set (FILAMENT ${CMAKE_CURRENT_SOURCE_DIR})

# Where our tools are
set (TOOLS ${CMAKE_CURRENT_SOURCE_DIR}/tools)

# ====================================================
# Compiler check
# ====================================================
set (MIN_CLANG_VERSION "5.0")

if (CMAKE_C_COMPILER_ID MATCHES "Clang")
    if (CMAKE_C_COMPILER_VERSION VERSION_LESS MIN_CLANG_VERSION)
        message(FATAL_ERROR "Detected C compiler Clang {CMAKE_C_COMPILER_VERSION} < ${MIN_CLANG_VERSION}")
    endif()
else()
    message(FATAL_ERROR "Detected C compiler ${CMAKE_C_COMPILER_ID} is unsupported")
endif()

# ====================================================
# General compiler flags
# ====================================================
set (CXX_STANDARD "-std=c++14")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_STANDARD} -fstrict-aliasing -Wno-unknown-pragmas -Who-unused-function")

if (USE_EXTERNAL_GLES3)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_EXTERNAL_GLES3")
endif()

if (LINUX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    if (FILAMENT_REQUIRES_CXXABI)
        # Required in CI environment with custom libc++ and libc++abi.
        link_libraries("-lc++abi")
    endif()
    # To distribute our binaries, we must remove the dependency on libc++ and libgcc.
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        link_libraries("-static-libgcc -static-libstdc++")
    endif()
else()
    if (FILAMENT_REQUIRES_CXXABI)
        message("The option FILAMENT_REQUIRES_CXXABI is unsupported on this platform")
    endif();
endif()

# ====================================================
# Sub-projects
# ====================================================
# spirv-tools must come before filamat, as filamat relies on the presence of the 
# spirv-tools_SOURCE_DIR variable.
add_subdirectory (${EXTERNAL}/spirv-tools)
add_subdirectory (${EXTERNAL}/glslang/tnt)

# Generate exported executables for cross-compiled builds (Android, WebGL, and iOS)
# This variable will be set to true by CMake if CMake is cross compiling.
if (NOT CMAKE_CROSSCOMPILING)
    export(TARGETS matc cmgen filamesh mipgen resgen FILE ${IMPORT_EXECUTABLES})
endif()
