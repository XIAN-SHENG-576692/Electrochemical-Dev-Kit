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

#include "electrochemical_config.h"

/**
 * @brief Macro to declare a Ramp definition with specific data types.
 * @param name        Prefix for the generated struct and functions.
 * @param bool_type   Type for boolean operations.
 * @param energy_type Type for voltage/potential values.
 * @param index_type  Type for step indices.
 * @param num_type    Type for count of steps.
 * @param rate_type   Type for scan rate calculations.
 * @param time_type   Type for time values.
 */
#define DEFINE_ELECTROCHEMICAL_RAMP(                                           \
    name,                                                                      \
    bool_type,                                                                 \
    energy_type,                                                               \
    index_type,                                                                \
    num_type,                                                                  \
    rate_type,                                                                 \
    time_type                                                                  \
)                                                                              \
    typedef struct                                                             \
    {                                                                          \
        energy_type e_begin; /**< Starting potential */                        \
        energy_type e_step;  /**< Increment per step */                        \
        time_type   t_step;  /**< Duration of the step */                      \
        num_type    n_step;  /**< Number of steps in the scan */               \
    } name##_params;                                                           \
                                                                               \
    static inline energy_type name##_get_e_end(const name##_params *const p)   \
    {                                                                          \
        return p->e_begin + (p->e_step * p->n_step);                           \
    }                                                                          \
                                                                               \
    static inline energy_type name##_get_energy_by_index(                      \
        const name##_params *const p,                                          \
        index_type                 index                                       \
    )                                                                          \
    {                                                                          \
        return p->e_begin + (p->e_step * index);                               \
    }                                                                          \
                                                                               \
    static inline rate_type name##_get_scan_rate(const name##_params *const p) \
    {                                                                          \
        rate_type e_step;                                                      \
        e_step = (p->e_step > 0) ? p->e_step : -p->e_step;                     \
        return e_step / (rate_type)p->t_step;                                  \
    }                                                                          \
                                                                               \
    static inline time_type name##_get_t_total(const name##_params *const p)   \
    {                                                                          \
        return p->t_step * p->n_step;                                          \
    }                                                                          \
                                                                               \
    static inline time_type name##_get_time_by_index(                          \
        const name##_params *const p,                                          \
        index_type                 index                                       \
    )                                                                          \
    {                                                                          \
        return p->t_step * index;                                              \
    }                                                                          \
                                                                               \
    static inline bool_type name##_is_vaild(const name##_params *const p)      \
    {                                                                          \
        return (p->e_step != 0) && (p->t_step > 0) && (p->n_step > 0);         \
    }                                                                          \
                                                                               \
    static inline void name##_set_n_step_by_e_end(                             \
        name##_params *const p,                                                \
        energy_type          e_end                                             \
    )                                                                          \
    {                                                                          \
        p->n_step = (e_end - p->e_begin) / p->e_step;                          \
        return;                                                                \
    }                                                                          \
                                                                               \
    static inline void name##_set_t_step_by_scan_rate(                         \
        name##_params *const p,                                                \
        rate_type            scan_rate                                         \
    )                                                                          \
    {                                                                          \
        rate_type e_step;                                                      \
        e_step    = (p->e_step > 0) ? p->e_step : -p->e_step;                  \
        p->t_step = (time_type)(e_step / scan_rate);                           \
        return;                                                                \
    }

#ifdef __cplusplus
}
#endif
