cmake_minimum_required(3.16)

project(govnotest)

# Allow user to toggle between static and shared library building
option(BUILD_SHARED_LIBS "Build shared libs" OFF)


option(AUIB_FORCE_PRECOMPILED "Use precompiled binary only" ON)

# Use AUI.Boot framework
# Set AUI framework version
set(AUI_VERSION v8.0.0-rc.8)
# Download AUI boot script from GitHub
file(
        DOWNLOAD
        https://raw.githubusercontent.com/aui-framework/aui/${AUI_VERSION}/aui.boot.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)
# Include downloaded AUI boot script
include(${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)


auib_import(govno https://github.com/Alex2772/govnolib
            VERSION v0.0.11
)

# Find all .cpp source files recursively in src directory
file(GLOB_RECURSE SRCS src/*.cpp)
# Create library target from collected sources
add_executable(govnotest ${SRCS})
# Set include directories for build and installation
target_include_directories(govnotest PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)