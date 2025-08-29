# Standard routine
cmake_minimum_required(VERSION 3.16)
project(example_app
        VERSION 0.0.11 # CI_PROJECT_VERSION
    )

option(BUILD_SHARED_LIBS "Build shared libs" OFF)
option(AUIB_FORCE_PRECOMPILED "AUI.Boot: force precompiled dependencies" OFF)
option(AUIB_NO_PRECOMPILED "AUI.Boot: disable precompiled dependencies" ON)

# Use AUI.Boot
set(AUI_VERSION v8.0.0-rc.8)
file(
        DOWNLOAD
        https://raw.githubusercontent.com/aui-framework/aui/${AUI_VERSION}/aui.boot.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)

file(GLOB_RECURSE SRCS src/*.cpp)
add_library(govnolib ${SRCS})
target_include_directories(govnolib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)
install(TARGETS govnolib
        EXPORT govnolib-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT govnolib-targets
        FILE govnolib-targets.cmake
        NAMESPACE govnolib::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/govnolib)

install(DIRECTORY src/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h"
        PATTERN "*.hpp")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        govnolib-config-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/govnolib-config-version.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/govnolib)



auib_precompiled_binary()
