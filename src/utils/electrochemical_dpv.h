#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "electrochemical_config.h"

/**
 * @brief X-Macro table for DPV selection.
 */
#define ELECTROCHEMICAL_DPV_SELECTION_TABLE \
    X(ALL,   0b00, step and pulse) \
    X(PULSE, 0b01, pulse) \
    X(STEP,  0b10, step) \

/**
 * @brief Enumeration of DPV selection modes derived from the X-Macro table.
 */
typedef enum {
    #define X(name, val, desc) ELECTROCHEMICAL_DPV_SELECTION_##name = val,
        ELECTROCHEMICAL_DPV_SELECTION_TABLE
    #undef X
} ELECTROCHEMICAL_DPV_SELECTION_ENUM;

/**
 * @brief Human-readable descriptions for each DPV selection mode.
 */
static const char *const ELECTROCHEMICAL_DPV_SELECTION_DESCRIPTIONS[] = {
    #define X(name, val, desc) #desc,
        ELECTROCHEMICAL_DPV_SELECTION_TABLE
    #undef X
};

/**
 * @brief Macro to declare a DPV implementation with specific data types.
 * @param name        Prefix for the generated struct and functions.
 * @param energy_type Type for voltage/potential values.
 * @param index_type  Type for step indices.
 * @param num_type    Type for count of steps.
 * @param rate_type   Type for scan rate calculations.
 * @param time_type   Type for time values.
 */
#define DECLARE_ELECTROCHEMICAL_DPV(name, energy_type, index_type, num_type, rate_type, time_type) \
    typedef struct { \
        energy_type e_begin; /**< Starting potential */ \
        energy_type e_pulse; /**< Pulse amplitude */ \
        energy_type e_step;  /**< Increment per step */ \
        time_type t_pulse;   /**< Duration of the pulse */ \
        time_type t_step;    /**< Duration of the step base */ \
        num_type n_step;     /**< Number of steps in the scan */ \
    } name##_params; \
\
    static inline energy_type name##_get_e_end(const name##_params *const p) { \
        return p->e_begin + (p->e_step * p->n_step); \
    } \
\
    static inline energy_type name##_get_energy_by_index(const name##_params *const p, index_type index, ELECTROCHEMICAL_DPV_SELECTION_ENUM selection) { \
        switch (selection) { \
            case ELECTROCHEMICAL_DPV_SELECTION_STEP: \
                return p->e_begin + (p->e_step * index); \
            case ELECTROCHEMICAL_DPV_SELECTION_PULSE: \
                return p->e_begin + (p->e_step * index) + p->e_pulse; \
            case ELECTROCHEMICAL_DPV_SELECTION_ALL: \
                return p->e_begin + (p->e_step * (index / 2)) + ((index % 2 == 0) ? 0 : p->e_pulse); \
            default: \
                return 0.0; \
        } \
    } \
\
    static inline num_type name##_get_n_step_total(const name##_params *const p) { \
        return p->n_step * 2; \
    } \
\
    static inline time_type name##_get_t_interval(const name##_params *const p); \
    static inline rate_type name##_get_scan_rate(const name##_params *const p) { \
        rate_type e_step; \
        e_step = (p->e_step > 0) ? p->e_step : -p->e_step; \
        return e_step / (rate_type) name##_get_t_interval(p); \
    } \
\
    static inline time_type name##_get_t_interval(const name##_params *const p) { \
        return p->t_step + p->t_pulse; \
    } \
\
    static inline time_type name##_get_t_total(const name##_params *const p) { \
        return name##_get_t_interval(p) * p->n_step; \
    } \
\
    static inline time_type name##_get_time_by_index(const name##_params *const p, index_type index, ELECTROCHEMICAL_DPV_SELECTION_ENUM selection) { \
        switch (selection) { \
            case ELECTROCHEMICAL_DPV_SELECTION_STEP: \
                return name##_get_t_interval(p) * index; \
            case ELECTROCHEMICAL_DPV_SELECTION_PULSE: \
                return name##_get_t_interval(p) * index + p->t_step; \
            case ELECTROCHEMICAL_DPV_SELECTION_ALL: \
                return name##_get_t_interval(p) * (index / 2) + ((index % 2 == 0) ? 0 : p->t_step); \
            default: \
                return 0.0; \
        } \
    } \

#ifdef __cplusplus
}
#endif
