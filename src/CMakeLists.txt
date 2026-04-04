add_library(Electrochemical INTERFACE)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "*.h")

target_precompile_headers(Electrochemical
    INTERFACE
        ${SRC_FILES}
)

target_include_directories(Electrochemical
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

add_subdirectory(config)
add_subdirectory(utils)
