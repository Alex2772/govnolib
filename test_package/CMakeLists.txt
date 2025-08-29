cmake_minimum_required(VERSION 3.16)

project(govnotest)

# Allow user to toggle between static and shared library building
option(BUILD_SHARED_LIBS "Build shared libs" OFF)
message(STATUS "CMAKE_VS_PLATFORM_TOOLSET=${CMAKE_VS_PLATFORM_TOOLSET}")

option(AUIB_FORCE_PRECOMPILED "Use precompiled binary only" ON)

# Use AUI.Boot framework
# Set AUI framework version
set(AUI_VERSION fa0cf5d68a340da4a6dd46cb8ea55f900e34cad2)
# Download AUI boot script from GitHub
file(
        DOWNLOAD
        https://raw.githubusercontent.com/aui-framework/aui/${AUI_VERSION}/aui.boot.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)
# Include downloaded AUI boot script
include(${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)

# Find all .cpp source files recursively in src directory
file(GLOB_RECURSE SRCS src/*.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create library target from collected sources
add_executable(${PROJECT_NAME} ${SRCS})

# add the govno library
auib_import(govno https://github.com/Alex2772/govnolib
        VERSION v0.0.2
)
target_link_libraries(${PROJECT_NAME} PUBLIC govno::govno)


# Set include directories for build and installation
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)
