add_executable(Demo)

target_compile_options(Demo
    PRIVATE
        -Wall
        -Werror
        -O3
)

# Sources
target_sources(Demo
    PRIVATE
        main.c
)

# Libraries
target_link_libraries(Demo
    PRIVATE
        Electrochemical
)
