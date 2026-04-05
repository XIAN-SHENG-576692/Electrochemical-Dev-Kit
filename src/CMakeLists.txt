add_library(electrochemical INTERFACE)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "*.h")

target_precompile_headers(electrochemical
    INTERFACE
        ${SRC_FILES}
)

target_include_directories(electrochemical
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_subdirectory(config)
add_subdirectory(utils)
