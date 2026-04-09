cmake_minimum_required(VERSION 3.23)

project(Electrochemical_Dev_Kit)

# Parameters
option(BUILD_DEMO "Build Demo" OFF)
option(BUILD_TESTS "Build Tests" OFF)

# Subdirectories
add_subdirectory(src)

# Test
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Demo
if(BUILD_DEMO)
    add_subdirectory(demo)
endif()
