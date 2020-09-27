cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(pftr)

# Specify C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PFTR_CORE_APPLICATION_TARGET "pftr")

if(WIN32)
    # Ensure that Windows code page independent prototypes are used,
    # i.e. Unicode only
    add_definitions(-DUNICODE -D_UNICODE)

    # Reduce the size of Windows headers by excluding Windows APIs
    # such as Cryptography, DDE, RPC, Shell and Windows Sockets
    add_definitions(-DWIN32_LEAN_AND_MEAN)

    # Enable strict Windows type checking
    add_definitions(-DSTRICT)

    # Do not define min and max macros to remove conflicts with the STL
    add_definitions(-DNOMINMAX)

    # Windows 7 is the minimum operating system version supported
    add_definitions(-DWINVER=0x0601 -D_WIN32_WINNT=0x0601)
endif()

# Third party dependencies
# Note: GLEW requires running automatic code generation before build
add_subdirectory(glew/build/cmake)
add_subdirectory(glfw)

# Include CMake extensions
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include("utility")

add_subdirectory(pftr)
