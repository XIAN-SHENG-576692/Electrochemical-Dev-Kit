#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#define ELECTROCHEMICAL_ERROR_TABLE                                            \
    X(OK, 0b00, No error)                                                      \
    X(PARAMS, 0b01, Invalid parameters)                                        \
    X(OTHER, 0b10, Other error)

    /** @{ */
    typedef enum
    {
#define X(name, val, desc) ELECTROCHEMICAL_ERROR_##name = val,
        ELECTROCHEMICAL_ERROR_TABLE
#undef X
    } ELECTROCHEMICAL_ERROR_ENUM;
    /** @} */

    static const char *const ELECTROCHEMICAL_ERROR_DESCRIPTIONS[] = {
#define X(name, val, desc) #desc,
        ELECTROCHEMICAL_ERROR_TABLE
#undef X
    };

#ifdef __cplusplus
}
#endif
