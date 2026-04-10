/**
 * @author    XIAN-SHENG CHEN
 * @date      April 2026
 *
 * Copyright (c) 2026 XIAN-SHENG CHEN. All Rights Reserved.
 **/
#include "electrochemical_dev_kit.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

ELECTROCHEMICAL_DEV_KIT_DEFINE_CV(__cv, float, uint8_t, float)
ELECTROCHEMICAL_DEV_KIT_DEFINE_DPV(__dpv, float, uint8_t, float)
ELECTROCHEMICAL_DEV_KIT_DEFINE_RAMP(__ramp, float, uint8_t, float)

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return -1;
    }

    if (strcmp(argv[1], "cv") == 0)
    {
        ELECTROCHEMICAL_DEV_KIT_cv_params cv = {
            .e_begin = 500,
            .e_step  = -10,
            .n_step  = 10,
            .t_step  = 5,
        };
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_at =
            ELECTROCHEMICAL_DEV_KIT_cv_get_e_at_index(&cv, 5);
        if (e_at != 450)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_vertex =
            ELECTROCHEMICAL_DEV_KIT_cv_get_e_vertex(&cv);
        if (e_vertex != 400)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE n_step_total =
            ELECTROCHEMICAL_DEV_KIT_cv_get_n_step_total(&cv);
        if (n_step_total != 20)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE scan_rate =
            ELECTROCHEMICAL_DEV_KIT_cv_get_scan_rate(&cv);
        if (scan_rate != 2)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_at =
            ELECTROCHEMICAL_DEV_KIT_cv_get_t_at_index(&cv, 5);
        if (t_at != 25)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_ramp =
            ELECTROCHEMICAL_DEV_KIT_cv_get_t_ramp(&cv);
        if (t_ramp != 50)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_total =
            ELECTROCHEMICAL_DEV_KIT_cv_get_t_total(&cv);
        if (t_total != 100)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE is_invaild =
            !ELECTROCHEMICAL_DEV_KIT_cv_is_vaild(&cv);
        if (is_invaild)
            return -1;
        {
            ELECTROCHEMICAL_DEV_KIT_cv_params cv_copy = cv;
            cv_copy.e_step                            = 0;
            ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE is_vaild =
                ELECTROCHEMICAL_DEV_KIT_cv_is_vaild(&cv_copy);
            if (is_vaild)
                return -1;
        }
        {
            ELECTROCHEMICAL_DEV_KIT_cv_params cv_copy = cv;
            ELECTROCHEMICAL_DEV_KIT_cv_set_n_step_by_e_vertex(&cv_copy, 400);
            ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_vertex_copy =
                ELECTROCHEMICAL_DEV_KIT_cv_get_e_vertex(&cv_copy);
            if (e_vertex_copy != 400)
                return -1;
        }
        {
            ELECTROCHEMICAL_DEV_KIT_cv_params cv_copy = cv;
            ELECTROCHEMICAL_DEV_KIT_cv_set_t_step_by_scan_rate(&cv_copy, 1.0);
            ELECTROCHEMICAL_DEV_KIT_RATE_TYPE scan_rate_copy =
                ELECTROCHEMICAL_DEV_KIT_cv_get_scan_rate(&cv_copy);
            if (scan_rate_copy != 1)
                return -1;
        }
        return 0;
    }
    else if (strcmp(argv[1], "dpv") == 0)
    {
        ELECTROCHEMICAL_DEV_KIT_dpv_params dpv = {
            .e_begin = 500,
            .e_pulse = 50,
            .e_step  = -10,
            .n_step  = 10,
            .t_pulse = 2,
            .t_step  = 8,
        };
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_at_pulse =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_e_at_index(
                &dpv,
                5,
                ELECTROCHEMICAL_DEV_KIT_dpv_selection_pulse
            );
        if (e_at_pulse != 500)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_at_step =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_e_at_index(
                &dpv,
                5,
                ELECTROCHEMICAL_DEV_KIT_dpv_selection_step
            );
        if (e_at_step != 450)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_at_step_pulse =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_e_at_index(
                &dpv,
                5,
                ELECTROCHEMICAL_DEV_KIT_dpv_selection_step_pulse
            );
        if (e_at_step_pulse != 530)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_end =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_e_end(&dpv);
        if (e_end != 400)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE n_step_total =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_n_step_total(&dpv);
        if (n_step_total != 20)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE scan_rate =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_scan_rate(&dpv);
        if (scan_rate != 1)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_at_pulse =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_t_at_index(
                &dpv,
                5,
                ELECTROCHEMICAL_DEV_KIT_dpv_selection_pulse
            );
        if (t_at_pulse != 58)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_at_step =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_t_at_index(
                &dpv,
                5,
                ELECTROCHEMICAL_DEV_KIT_dpv_selection_step
            );
        if (t_at_step != 50)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_at_step_pulse =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_t_at_index(
                &dpv,
                5,
                ELECTROCHEMICAL_DEV_KIT_dpv_selection_step_pulse
            );
        if (t_at_step_pulse != 28)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_interval =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_t_interval(&dpv);
        if (t_interval != 10)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_total =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_t_total(&dpv);
        if (t_total != 100)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE is_invaild =
            !ELECTROCHEMICAL_DEV_KIT_dpv_is_vaild(&dpv);
        if (is_invaild)
            return -1;
        {
            ELECTROCHEMICAL_DEV_KIT_dpv_params dpv_copy = dpv;
            dpv_copy.e_step                             = 0;
            ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE is_vaild =
                ELECTROCHEMICAL_DEV_KIT_dpv_is_vaild(&dpv_copy);
            if (is_vaild)
                return -1;
        }
        {
            ELECTROCHEMICAL_DEV_KIT_dpv_params dpv_copy = dpv;
            ELECTROCHEMICAL_DEV_KIT_dpv_set_n_step_by_e_end(&dpv_copy, 400);
            ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_end_copy =
                ELECTROCHEMICAL_DEV_KIT_dpv_get_e_end(&dpv_copy);
            if (e_end_copy != 400)
                return -1;
        }
        {
            ELECTROCHEMICAL_DEV_KIT_dpv_params dpv_copy = dpv;
            ELECTROCHEMICAL_DEV_KIT_dpv_set_t_step_by_scan_rate(&dpv_copy, 1.0);
            ELECTROCHEMICAL_DEV_KIT_RATE_TYPE scan_rate_copy =
                ELECTROCHEMICAL_DEV_KIT_dpv_get_scan_rate(&dpv_copy);
            if (scan_rate_copy != 1)
                return -1;
        }
        return 0;
    }
    else if (strcmp(argv[1], "ramp") == 0)
    {
        ELECTROCHEMICAL_DEV_KIT_ramp_params ramp = {
            .e_begin = 500,
            .e_step  = -10,
            .n_step  = 10,
            .t_step  = 5,
        };
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_at =
            ELECTROCHEMICAL_DEV_KIT_ramp_get_e_at_index(&ramp, 5);
        if (e_at != 450)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_end =
            ELECTROCHEMICAL_DEV_KIT_ramp_get_e_end(&ramp);
        if (e_end != 400)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE scan_rate =
            ELECTROCHEMICAL_DEV_KIT_ramp_get_scan_rate(&ramp);
        if (scan_rate != 2)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_at =
            ELECTROCHEMICAL_DEV_KIT_ramp_get_t_at_index(&ramp, 5);
        if (t_at != 25)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_total =
            ELECTROCHEMICAL_DEV_KIT_ramp_get_t_total(&ramp);
        if (t_total != 50)
            return -1;
        ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE is_invaild =
            !ELECTROCHEMICAL_DEV_KIT_ramp_is_vaild(&ramp);
        if (is_invaild)
            return -1;
        {
            ELECTROCHEMICAL_DEV_KIT_ramp_params ramp_copy = ramp;
            ramp_copy.e_step                              = 0;
            ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE is_vaild =
                ELECTROCHEMICAL_DEV_KIT_ramp_is_vaild(&ramp_copy);
            if (is_vaild)
                return -1;
        }
        {
            ELECTROCHEMICAL_DEV_KIT_ramp_params ramp_copy = ramp;
            ELECTROCHEMICAL_DEV_KIT_ramp_set_n_step_by_e_end(&ramp_copy, 400);
            ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_end_copy =
                ELECTROCHEMICAL_DEV_KIT_ramp_get_e_end(&ramp_copy);
            if (e_end_copy != 400)
                return -1;
        }
        {
            ELECTROCHEMICAL_DEV_KIT_ramp_params ramp_copy = ramp;
            ELECTROCHEMICAL_DEV_KIT_ramp_set_t_step_by_scan_rate(
                &ramp_copy,
                1.0
            );
            ELECTROCHEMICAL_DEV_KIT_RATE_TYPE scan_rate_copy =
                ELECTROCHEMICAL_DEV_KIT_ramp_get_scan_rate(&ramp_copy);
            if (scan_rate_copy != 1)
                return -1;
        }
        return 0;
    }

    return -1;
}
