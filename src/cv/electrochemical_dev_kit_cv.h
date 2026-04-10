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

#include <stdbool.h>
#include <stdint.h>

    typedef struct
    {
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_begin; /**< Starting potential */
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_step;  /**< Increment per step */
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE   t_step; /**< Duration of the step */
        ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE
        n_step; /**< Number of steps in the scan */
    } ELECTROCHEMICAL_DEV_KIT_cv_params;

    inline ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE
    ELECTROCHEMICAL_DEV_KIT_cv_get_e_at_index(
        const ELECTROCHEMICAL_DEV_KIT_cv_params *const p,
        ELECTROCHEMICAL_DEV_KIT_INDEX_TYPE             index
    )
    {
        return p->e_begin +
               (p->e_step *
                ((index > p->n_step) ? (2 * p->n_step - index) : index));
    }

    inline ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE
    ELECTROCHEMICAL_DEV_KIT_cv_get_e_vertex(
        const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
    )
    {
        return p->e_begin + (p->e_step * p->n_step);
    }

    inline ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE
    ELECTROCHEMICAL_DEV_KIT_cv_get_n_step_total(
        const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
    )
    {
        return p->n_step * 2;
    }

    inline ELECTROCHEMICAL_DEV_KIT_RATE_TYPE
    ELECTROCHEMICAL_DEV_KIT_cv_get_scan_rate(
        const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
    )
    {
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE e_step;
        e_step = (p->e_step > 0) ? p->e_step : -p->e_step;
        return e_step / (ELECTROCHEMICAL_DEV_KIT_RATE_TYPE)p->t_step;
    }

    inline ELECTROCHEMICAL_DEV_KIT_TIME_TYPE
    ELECTROCHEMICAL_DEV_KIT_cv_get_t_at_index(
        const ELECTROCHEMICAL_DEV_KIT_cv_params *const p,
        ELECTROCHEMICAL_DEV_KIT_INDEX_TYPE             index
    )
    {
        return p->t_step * index;
    }

    inline ELECTROCHEMICAL_DEV_KIT_TIME_TYPE
    ELECTROCHEMICAL_DEV_KIT_cv_get_t_ramp(
        const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
    )
    {
        return p->t_step * p->n_step;
    }

    inline ELECTROCHEMICAL_DEV_KIT_TIME_TYPE
    ELECTROCHEMICAL_DEV_KIT_cv_get_t_total(
        const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
    )
    {
        return p->t_step * p->n_step * 2;
    }

    inline ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE
    ELECTROCHEMICAL_DEV_KIT_cv_is_vaild(
        const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
    )
    {
        return (p->e_step != 0) && (p->t_step > 0) && (p->n_step > 0);
    }

    inline void ELECTROCHEMICAL_DEV_KIT_cv_set_n_step_by_e_vertex(
        ELECTROCHEMICAL_DEV_KIT_cv_params *const p,
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE      e_vertex
    )
    {
        p->n_step = (e_vertex - p->e_begin) / p->e_step;
        return;
    }

    inline void ELECTROCHEMICAL_DEV_KIT_cv_set_t_step_by_scan_rate(
        ELECTROCHEMICAL_DEV_KIT_cv_params *const p,
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE        scan_rate
    )
    {
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE e_step;
        e_step    = (p->e_step > 0) ? p->e_step : -p->e_step;
        p->t_step = (ELECTROCHEMICAL_DEV_KIT_TIME_TYPE)(e_step / scan_rate);
        return;
    }

/**
 * @brief Macro to declare a CV definition with specific data types.
 * @param name        Prefix for the generated struct and functions.
 * @param energy_type Type for voltage/potential values.
 * @param number_type Type for count of steps.
 * @param time_type   Type for time values.
 */
#define ELECTROCHEMICAL_DEV_KIT_DEFINE_CV(                                     \
    name,                                                                      \
    energy_type,                                                               \
    number_type,                                                               \
    time_type                                                                  \
)                                                                              \
    typedef struct                                                             \
    {                                                                          \
        energy_type e_begin; /**< Starting potential */                        \
        energy_type e_step;  /**< Increment per step */                        \
        time_type   t_step;  /**< Duration of the step */                      \
        number_type n_step;  /**< Number of steps in the scan */               \
    } name##_params;

#ifdef __cplusplus
}
#endif
