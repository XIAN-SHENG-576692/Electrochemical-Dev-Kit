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
 * @brief Macro to declare a CV definition with specific data types.
 * @param name        Prefix for the generated struct and functions.
 * @param energy_type Type for voltage/potential values.
 * @param index_type  Type for step indices.
 * @param num_type    Type for count of steps.
 * @param rate_type   Type for scan rate calculations.
 * @param time_type   Type for time values.
 */
#define DECLARE_ELECTROCHEMICAL_CV_H(                                          \
    name,                                                                      \
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
    inline energy_type name##_get_e_vertex(const name##_params *const p);      \
                                                                               \
    inline energy_type name##_get_energy_by_index(                             \
        const name##_params *const p,                                          \
        index_type                 index                                       \
    );                                                                         \
                                                                               \
    inline num_type name##_get_n_step_total(const name##_params *const p);     \
                                                                               \
    inline rate_type name##_get_scan_rate(const name##_params *const p);       \
                                                                               \
    inline time_type name##_get_t_ramp(const name##_params *const p);          \
                                                                               \
    inline time_type name##_get_t_total(const name##_params *const p);         \
                                                                               \
    inline time_type name##_get_time_by_index(                                 \
        const name##_params *const p,                                          \
        index_type                 index                                       \
    );                                                                         \
    inline void name##_set_n_step_by_e_vertex(                                 \
        name##_params *const p,                                                \
        energy_type          e_vertex                                          \
    );                                                                         \
    inline void name##_set_t_step_by_scan_rate(                                \
        name##_params *const p,                                                \
        rate_type            scan_rate                                         \
    );

/**
 * @brief Macro to declare a CV implementation with specific data types.
 * @param name        Prefix for the generated struct and functions.
 * @param energy_type Type for voltage/potential values.
 * @param index_type  Type for step indices.
 * @param num_type    Type for count of steps.
 * @param rate_type   Type for scan rate calculations.
 * @param time_type   Type for time values.
 */
#define DECLARE_ELECTROCHEMICAL_CV_C(                                          \
    name,                                                                      \
    energy_type,                                                               \
    index_type,                                                                \
    num_type,                                                                  \
    rate_type,                                                                 \
    time_type                                                                  \
)                                                                              \
    inline energy_type name##_get_e_vertex(const name##_params *const p)       \
    {                                                                          \
        return p->e_begin + (p->e_step * p->n_step);                           \
    }                                                                          \
                                                                               \
    inline energy_type name##_get_energy_by_index(                             \
        const name##_params *const p,                                          \
        index_type                 index                                       \
    )                                                                          \
    {                                                                          \
        return p->e_begin +                                                    \
               (p->e_step *                                                    \
                ((index > p->n_step) ? (2 * p->n_step - index) : index));      \
    }                                                                          \
                                                                               \
    inline num_type name##_get_n_step_total(const name##_params *const p)      \
    {                                                                          \
        return p->n_step * 2;                                                  \
    }                                                                          \
                                                                               \
    inline rate_type name##_get_scan_rate(const name##_params *const p)        \
    {                                                                          \
        rate_type e_step;                                                      \
        e_step = (p->e_step > 0) ? p->e_step : -p->e_step;                     \
        return e_step / (rate_type)p->t_step;                                  \
    }                                                                          \
                                                                               \
    inline time_type name##_get_t_ramp(const name##_params *const p)           \
    {                                                                          \
        return p->t_step * p->n_step;                                          \
    }                                                                          \
                                                                               \
    inline time_type name##_get_t_total(const name##_params *const p)          \
    {                                                                          \
        return p->t_step * p->n_step * 2;                                      \
    }                                                                          \
                                                                               \
    inline time_type name##_get_time_by_index(                                 \
        const name##_params *const p,                                          \
        index_type                 index                                       \
    )                                                                          \
    {                                                                          \
        return p->t_step * index;                                              \
    }                                                                          \
    inline void name##_set_n_step_by_e_vertex(                                 \
        name##_params *const p,                                                \
        energy_type          e_vertex                                          \
    )                                                                          \
    {                                                                          \
        p->n_step = (e_vertex - p->e_begin) / p->e_step;                       \
        return;                                                                \
    }                                                                          \
    inline void name##_set_t_step_by_scan_rate(                                \
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
