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

/**
 * @brief X-Macro table for DPV selection.
 */
#define ELECTROCHEMICAL_DEV_KIT_DPV_SELECTION_TABLE                            \
    X(pulse, 0b00)                                                             \
    X(step, 0b01)                                                              \
    X(step_pulse, 0b10)

    /**
     * @brief Enumeration of DPV selection modes derived from the X-Macro table.
     */
    typedef enum
    {
#define X(name, val) ELECTROCHEMICAL_DEV_KIT_dpv_selection_##name = val,
        ELECTROCHEMICAL_DEV_KIT_DPV_SELECTION_TABLE
#undef X
    } ELECTROCHEMICAL_DEV_KIT_dpv_selection_enum;

    typedef struct
    {
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_begin; /**< Starting potential */
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_pulse; /**< Pulse amplitude */
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_step;  /**< Increment per step */
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_pulse; /**< Duration of the pulse */
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE
        t_step; /**< Duration of the step base */
        ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE
        n_step; /**< Number of steps in the scan */
    } ELECTROCHEMICAL_DEV_KIT_dpv_params;

    inline ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE
    ELECTROCHEMICAL_DEV_KIT_dpv_get_e_at_index(
        const ELECTROCHEMICAL_DEV_KIT_dpv_params *const p,
        ELECTROCHEMICAL_DEV_KIT_INDEX_TYPE              index,
        ELECTROCHEMICAL_DEV_KIT_dpv_selection_enum      selection
    )
    {
        switch (selection)
        {
            case ELECTROCHEMICAL_DEV_KIT_dpv_selection_pulse:
                return p->e_begin + (p->e_step * index) + p->e_pulse;
            case ELECTROCHEMICAL_DEV_KIT_dpv_selection_step:
                return p->e_begin + (p->e_step * index);
            case ELECTROCHEMICAL_DEV_KIT_dpv_selection_step_pulse:
                return p->e_begin + (p->e_step * (index / 2)) +
                       ((index % 2 == 0) ? 0 : p->e_pulse);
            default:
                return 0.0;
        }
    }

    inline ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE
    ELECTROCHEMICAL_DEV_KIT_dpv_get_e_end(
        const ELECTROCHEMICAL_DEV_KIT_dpv_params *const p
    )
    {
        return p->e_begin + (p->e_step * p->n_step);
    }

    inline ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE
    ELECTROCHEMICAL_DEV_KIT_dpv_get_n_step_total(
        const ELECTROCHEMICAL_DEV_KIT_dpv_params *const p
    )
    {
        return p->n_step * 2;
    }

    inline ELECTROCHEMICAL_DEV_KIT_TIME_TYPE
    ELECTROCHEMICAL_DEV_KIT_dpv_get_t_interval(
        const ELECTROCHEMICAL_DEV_KIT_dpv_params *const p
    )
    {
        return p->t_step + p->t_pulse;
    }

    inline ELECTROCHEMICAL_DEV_KIT_RATE_TYPE
    ELECTROCHEMICAL_DEV_KIT_dpv_get_scan_rate(
        const ELECTROCHEMICAL_DEV_KIT_dpv_params *const p
    )
    {
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE e_step;
        e_step = (p->e_step > 0) ? p->e_step : -p->e_step;
        return e_step / (ELECTROCHEMICAL_DEV_KIT_RATE_TYPE
                        )ELECTROCHEMICAL_DEV_KIT_dpv_get_t_interval(p);
    }

    inline ELECTROCHEMICAL_DEV_KIT_TIME_TYPE
    ELECTROCHEMICAL_DEV_KIT_dpv_get_t_at_index(
        const ELECTROCHEMICAL_DEV_KIT_dpv_params *const p,
        ELECTROCHEMICAL_DEV_KIT_INDEX_TYPE              index,
        ELECTROCHEMICAL_DEV_KIT_dpv_selection_enum      selection
    )
    {
        switch (selection)
        {
            case ELECTROCHEMICAL_DEV_KIT_dpv_selection_pulse:
                return ELECTROCHEMICAL_DEV_KIT_dpv_get_t_interval(p) * index +
                       p->t_step;
            case ELECTROCHEMICAL_DEV_KIT_dpv_selection_step:
                return ELECTROCHEMICAL_DEV_KIT_dpv_get_t_interval(p) * index;
            case ELECTROCHEMICAL_DEV_KIT_dpv_selection_step_pulse:
                return ELECTROCHEMICAL_DEV_KIT_dpv_get_t_interval(p) *
                           (index / 2) +
                       ((index % 2 == 0) ? 0 : p->t_step);
            default:
                return 0.0;
        }
    }

    inline ELECTROCHEMICAL_DEV_KIT_TIME_TYPE
    ELECTROCHEMICAL_DEV_KIT_dpv_get_t_total(
        const ELECTROCHEMICAL_DEV_KIT_dpv_params *const p
    )
    {
        return ELECTROCHEMICAL_DEV_KIT_dpv_get_t_interval(p) * p->n_step;
    }

    inline ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE
    ELECTROCHEMICAL_DEV_KIT_dpv_is_vaild(
        const ELECTROCHEMICAL_DEV_KIT_dpv_params *const p
    )
    {
        return (p->e_step != 0) && (p->t_step > 0) && (p->t_pulse > 0) &&
               (p->n_step > 0);
    }

    inline void ELECTROCHEMICAL_DEV_KIT_dpv_set_n_step_by_e_end(
        ELECTROCHEMICAL_DEV_KIT_dpv_params *const p,
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE       e_end
    )
    {
        p->n_step = (e_end - p->e_begin) / p->e_step;
        return;
    }

    inline void ELECTROCHEMICAL_DEV_KIT_dpv_set_t_step_by_scan_rate(
        ELECTROCHEMICAL_DEV_KIT_dpv_params *const p,
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE         scan_rate
    )
    {
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE e_step;
        e_step    = (p->e_step > 0) ? p->e_step : -p->e_step;
        p->t_step = (ELECTROCHEMICAL_DEV_KIT_TIME_TYPE)(e_step / scan_rate) -
                    p->t_pulse;
        return;
    }
/**
 * @brief Macro to declare a DPV definition with specific data types.
 * @param name        Prefix for the generated struct and functions.
 * @param energy_type Type for voltage/potential values.
 * @param number_type Type for count of steps.
 * @param time_type   Type for time values.
 */
#define ELECTROCHEMICAL_DEV_KIT_DEFINE_DPV(                                    \
    name,                                                                      \
    energy_type,                                                               \
    number_type,                                                               \
    time_type                                                                  \
)                                                                              \
    typedef struct                                                             \
    {                                                                          \
        energy_type e_begin; /**< Starting potential */                        \
        energy_type e_pulse; /**< Pulse amplitude */                           \
        energy_type e_step;  /**< Increment per step */                        \
        time_type   t_pulse; /**< Duration of the pulse */                     \
        time_type   t_step;  /**< Duration of the step base */                 \
        number_type n_step;  /**< Number of steps in the scan */               \
    } name##_params;

#ifdef __cplusplus
}
#endif
