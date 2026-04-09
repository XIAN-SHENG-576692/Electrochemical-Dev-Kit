add_executable(tests)

target_compile_options(
    tests
    PRIVATE
        -Wall
        -Werror
        -O3
)

# Sources
target_sources(
    tests
    PRIVATE
        main.c
)

# Libraries
target_link_libraries(
    tests
    PRIVATE
        electrochemical
)

function(AddTest op)
    add_test(
        NAME ${op}
        COMMAND tests ${op}
    )
endfunction()

AddTest(cv)
AddTest(dpv)
AddTest(ramp)
