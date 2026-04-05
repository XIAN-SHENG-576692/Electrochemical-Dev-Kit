#include "electrochemical.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define ENERGY_TYPE int16_t
#define INDEX_TYPE  uint8_t
#define NUM_TYPE    uint8_t
#define RATE_TYPE   float
#define TIME_TYPE   uint16_t

DECLARE_ELECTROCHEMICAL_CV_H(
    cv,
    ENERGY_TYPE,
    INDEX_TYPE,
    NUM_TYPE,
    RATE_TYPE,
    TIME_TYPE
)
DECLARE_ELECTROCHEMICAL_CV_C(
    cv,
    ENERGY_TYPE,
    INDEX_TYPE,
    NUM_TYPE,
    RATE_TYPE,
    TIME_TYPE
)
DECLARE_ELECTROCHEMICAL_DPV_H(
    dpv,
    ENERGY_TYPE,
    INDEX_TYPE,
    NUM_TYPE,
    RATE_TYPE,
    TIME_TYPE
)
DECLARE_ELECTROCHEMICAL_DPV_C(
    dpv,
    ENERGY_TYPE,
    INDEX_TYPE,
    NUM_TYPE,
    RATE_TYPE,
    TIME_TYPE
)
DECLARE_ELECTROCHEMICAL_RAMP_H(
    ramp,
    ENERGY_TYPE,
    INDEX_TYPE,
    NUM_TYPE,
    RATE_TYPE,
    TIME_TYPE
)
DECLARE_ELECTROCHEMICAL_RAMP_C(
    ramp,
    ENERGY_TYPE,
    INDEX_TYPE,
    NUM_TYPE,
    RATE_TYPE,
    TIME_TYPE
)

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return -1;
    }

    if (strcmp(argv[1], "cv") == 0)
    {
        cv_params cv = {
            .e_begin = 500,
            .e_step  = -10,
            .n_step  = 10,
            .t_step  = 5,
        };
        ENERGY_TYPE e_vertex = cv_get_e_vertex(&cv);
        if (e_vertex != 400)
            return -1;
        ENERGY_TYPE e_energy = cv_get_energy_by_index(&cv, 5);
        if (e_energy != 450)
            return -1;
        NUM_TYPE n_step_total = cv_get_n_step_total(&cv);
        if (n_step_total != 20)
            return -1;
        RATE_TYPE scan_rate = cv_get_scan_rate(&cv);
        if (scan_rate != 2)
            return -1;
        TIME_TYPE t_ramp = cv_get_t_ramp(&cv);
        if (t_ramp != 50)
            return -1;
        TIME_TYPE t_total = cv_get_t_total(&cv);
        if (t_total != 100)
            return -1;
        TIME_TYPE t_time = cv_get_time_by_index(&cv, 5);
        if (t_time != 25)
            return -1;
        return 0;
    }
    else if (strcmp(argv[1], "dpv") == 0)
    {
        dpv_params dpv = {
            .e_begin = 500,
            .e_pulse = 50,
            .e_step  = -10,
            .n_step  = 10,
            .t_pulse = 2,
            .t_step  = 8,
        };
        ENERGY_TYPE e_end = dpv_get_e_end(&dpv);
        if (e_end != 400)
            return -1;
        ENERGY_TYPE e_energy_pulse = dpv_get_energy_by_index(
            &dpv,
            5,
            ELECTROCHEMICAL_DPV_SELECTION_PULSE
        );
        if (e_energy_pulse != 500)
            return -1;
        ENERGY_TYPE e_energy_step = dpv_get_energy_by_index(
            &dpv,
            5,
            ELECTROCHEMICAL_DPV_SELECTION_STEP
        );
        if (e_energy_step != 450)
            return -1;
        ENERGY_TYPE e_energy_step_pulse = dpv_get_energy_by_index(
            &dpv,
            5,
            ELECTROCHEMICAL_DPV_SELECTION_STEP_PULSE
        );
        if (e_energy_step_pulse != 530)
            return -1;
        NUM_TYPE n_step_total = dpv_get_n_step_total(&dpv);
        if (n_step_total != 20)
            return -1;
        RATE_TYPE scan_rate = dpv_get_scan_rate(&dpv);
        if (scan_rate != 1)
            return -1;
        TIME_TYPE t_interval = dpv_get_t_interval(&dpv);
        if (t_interval != 10)
            return -1;
        TIME_TYPE t_total = dpv_get_t_total(&dpv);
        if (t_total != 100)
            return -1;
        TIME_TYPE t_time_pulse =
            dpv_get_time_by_index(&dpv, 5, ELECTROCHEMICAL_DPV_SELECTION_PULSE);
        if (t_time_pulse != 58)
            return -1;
        TIME_TYPE t_time_step =
            dpv_get_time_by_index(&dpv, 5, ELECTROCHEMICAL_DPV_SELECTION_STEP);
        if (t_time_step != 50)
            return -1;
        TIME_TYPE t_time_step_pulse = dpv_get_time_by_index(
            &dpv,
            5,
            ELECTROCHEMICAL_DPV_SELECTION_STEP_PULSE
        );
        if (t_time_step_pulse != 28)
            return -1;
        return 0;
    }
    else if (strcmp(argv[1], "ramp") == 0)
    {
        ramp_params ramp = {
            .e_begin = 500,
            .e_step  = -10,
            .n_step  = 10,
            .t_step  = 5,
        };
        ENERGY_TYPE e_end = ramp_get_e_end(&ramp);
        if (e_end != 400)
            return -1;
        ENERGY_TYPE e_energy = ramp_get_energy_by_index(&ramp, 5);
        if (e_energy != 450)
            return -1;
        RATE_TYPE scan_rate = ramp_get_scan_rate(&ramp);
        if (scan_rate != 2)
            return -1;
        TIME_TYPE t_total = ramp_get_t_total(&ramp);
        if (t_total != 50)
            return -1;
        TIME_TYPE t_time = ramp_get_time_by_index(&ramp, 5);
        if (t_time != 25)
            return -1;
        return 0;
    }

    return -1;
}
