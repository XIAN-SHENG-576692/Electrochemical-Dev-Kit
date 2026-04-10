add_library(electrochemical_dev_kit)

file(GLOB SRC_FILES CONFIGURE_DEPENDS "*.h")

target_precompile_headers(
    electrochemical_dev_kit
    PUBLIC
        ${SRC_FILES}
)

target_include_directories(
    electrochemical_dev_kit
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_subdirectory(cv)
add_subdirectory(dpv)
add_subdirectory(ramp)
