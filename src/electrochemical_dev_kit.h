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

#if !defined(ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE)
    #error "ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE: Type for boolean operations."
#endif

#if !defined(ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE)
    #error                                                                     \
        "ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE: Type for voltage/potential values."
#endif

#if !defined(ELECTROCHEMICAL_DEV_KIT_INDEX_TYPE)
    #error "ELECTROCHEMICAL_DEV_KIT_INDEX_TYPE: Type for step indices."
#endif

#if !defined(ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE)
    #error "ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE: Type for count of steps."
#endif

#if !defined(ELECTROCHEMICAL_DEV_KIT_RATE_TYPE)
    #error "ELECTROCHEMICAL_DEV_KIT_RATE_TYPE: Type for scan rate calculations."
#endif

#if !defined(ELECTROCHEMICAL_DEV_KIT_TIME_TYPE)
    #error "ELECTROCHEMICAL_DEV_KIT_TIME_TYPE: Type for time values."
#endif

#include "electrochemical_dev_kit_cv.h"
#include "electrochemical_dev_kit_dpv.h"
#include "electrochemical_dev_kit_ramp.h"

#ifdef __cplusplus
}
#endif
