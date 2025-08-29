# Specify minimum CMake version required to build the project
cmake_minimum_required(VERSION 3.16)
# Define project name and version
project(govno
        VERSION 0.0.11 # CI_PROJECT_VERSION
    )

# Allow user to toggle between static and shared library building
option(BUILD_SHARED_LIBS "Build shared libs" OFF)

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

# Find all .cpp source files recursively in src directory
file(GLOB_RECURSE SRCS src/*.cpp)
# Create library target from collected sources
add_library(govno ${SRCS})
# Set include directories for build and installation
target_include_directories(govno PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

# Include standard GNU installation directories definitions
include(GNUInstallDirs)
# Install library binaries and export targets
install(TARGETS govno
        EXPORT govno-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install CMake targets file for downstream projects
install(EXPORT govno-targets
        FILE govno-targets.cmake
        NAMESPACE govno::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/govno)

# Install header files
install(DIRECTORY src/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h"
        PATTERN "*.hpp")

# Include helpers for creating config files
include(CMakePackageConfigHelpers)

# Generate package version file
write_basic_package_version_file(
        govno-config-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

# Install config version file
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/govno-config-version.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/govno)


# Configure precompiled binary settings for AUI framework
auib_precompiled_binary()
