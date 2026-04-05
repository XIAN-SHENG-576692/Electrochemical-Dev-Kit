/**
 * @author    XIAN-SHENG CHEN
 * @date      April 2026
 *
 * Copyright (c) 2026 XIAN-SHENG CHEN. All Rights Reserved.
 **/
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#define ELECTROCHEMICAL_ERROR_TABLE                                            \
    X(OK, 0b00, No error)                                                      \
    X(PARAM, 0b01, Invalid parameter)                                          \
    X(DIV_0, 0b10, Division by zero)                                           \
    X(UNKNOWN, 0b11, Unknown error)

    /** @{ */
    typedef enum
    {
#define X(name, val, desc) ELECTROCHEMICAL_ERROR_##name = val,
        ELECTROCHEMICAL_ERROR_TABLE
#undef X
    } ELECTROCHEMICAL_ERROR_ENUM;
    /** @} */

#ifdef __cplusplus
}
#endif
