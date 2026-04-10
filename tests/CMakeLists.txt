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
        electrochemical_dev_kit
)

target_compile_definitions(
    electrochemical_dev_kit
        PUBLIC ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE=bool
        PUBLIC ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE=int16_t
        PUBLIC ELECTROCHEMICAL_DEV_KIT_INDEX_TYPE=uint8_t
        PUBLIC ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE=uint8_t
        PUBLIC ELECTROCHEMICAL_DEV_KIT_RATE_TYPE=float
        PUBLIC ELECTROCHEMICAL_DEV_KIT_TIME_TYPE=uint16_t
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
