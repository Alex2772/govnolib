# Specify minimum CMake version required to build the project
cmake_minimum_required(VERSION 3.16)
# Define project name and version
project(govno
        VERSION 0.0.2 # CI_PROJECT_VERSION
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
add_library(${PROJECT_NAME} ${SRCS})


set(TARGETS_EXPORT_NAME ${PROJECT_NAME}-targets)

# Global includes. Used by all targets
# Note:
#   * header location in project: src/*.h
#   * header location when installed: include/*.h
#   * header can be included by C++ code `#include <govno.h>`
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

# Introduce variables:
# * CMAKE_INSTALL_LIBDIR
# * CMAKE_INSTALL_BINDIR
# * CMAKE_INSTALL_INCLUDEDIR
include(GNUInstallDirs)

# Targets:
#   * <prefix>/lib/libgovno.a
#   * header location after install: <prefix>/include/govno.h
#   * headers can be included by C++ code `#include <govno.h>`
install(TARGETS ${PROJECT_NAME}
        EXPORT ${TARGETS_EXPORT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install CMake targets file for downstream projects:
#   * <prefix>/lib/cmake/govno/govno-targets.cmake
install(EXPORT ${TARGETS_EXPORT_NAME}
        FILE ${TARGETS_EXPORT_NAME}.cmake
        NAMESPACE "${PROJECT_NAME}::"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

# Install header files
install(DIRECTORY src/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h"
        PATTERN "*.hpp")

# Include helpers for creating config files
include(CMakePackageConfigHelpers)


# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * TARGETS_EXPORT_NAME
#   * PROJECT_NAME
configure_package_config_file(
        "cmake/config.cmake.in"
        "${PROJECT_NAME}-config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

# Configure '<PROJECT-NAME>-config-version.cmake'
# Use:
#   * PROJECT_NAME
#   * PROJECT_VERSION
write_basic_package_version_file(
        ${PROJECT_NAME}-config-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

# Install config version file
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})


# Configure precompiled binary settings for AUI framework
auib_precompiled_binary()
