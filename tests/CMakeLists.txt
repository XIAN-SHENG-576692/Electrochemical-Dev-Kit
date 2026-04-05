add_executable(Tests)

target_compile_options(Tests
    PRIVATE
        -Wall
        -Werror
        -O3
)

# Sources
target_sources(Tests
    PRIVATE
        main.c
)

# Libraries
target_link_libraries(Tests
    PRIVATE
        Electrochemical
)

function(AddTest op)
    add_test(
        NAME ${op}
        COMMAND Tests ${op}
    )
endfunction()

AddTest(cv)
AddTest(dpv)
AddTest(ramp)
