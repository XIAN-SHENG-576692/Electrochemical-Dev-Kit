cmake_minimum_required(VERSION 3.23)

project(Electrochemical_Dev_Kit)

# Parameters
option(ELECTROCHEMICAL_BUILD_DEMO "Electrochemical Build Demo" OFF)
option(ELECTROCHEMICAL_BUILD_TESTS "Electrochemical Build Tests" OFF)

# Subdirectories
add_subdirectory(src)

# Test
if(ELECTROCHEMICAL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Demo
if(ELECTROCHEMICAL_BUILD_DEMO)
    add_subdirectory(demo)
endif()
