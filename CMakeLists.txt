# Standard routine
cmake_minimum_required(VERSION 3.16)
project(example_app
        VERSION 0.0.11 # CI_PROJECT_VERSION
    )

set(CPACK_GENERATOR "ZIP" CACHE STRING "")

option(BUILD_SHARED_LIBS "Build shared libs" OFF)
option(AUIB_FORCE_PRECOMPILED "AUI.Boot: force precompiled dependencies" OFF)
option(AUIB_NO_PRECOMPILED "AUI.Boot: disable precompiled dependencies" ON)

# Use AUI.Boot
file(
        DOWNLOAD
        https://raw.githubusercontent.com/aui-framework/aui/${AUI_VERSION}/aui.boot.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)

file(GLOB_RECURSE SRCS src/*.cpp)
add_library(govnolib ${SRCS})

include(CPack)