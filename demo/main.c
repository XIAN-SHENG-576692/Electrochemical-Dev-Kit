/**
 * @author    XIAN-SHENG CHEN
 * @date      April 2026
 *
 * Copyright (c) 2026 XIAN-SHENG CHEN. All Rights Reserved.
 **/
#include "electrochemical_dev_kit.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** ==================== Declaration ==================== */
static const char *program_invocation_name;

// Macro to stringize the given argument
#define STRINGIZE_THIS(var)            #var
#define STRINGIZE_THIS_DEFINITION(var) STRINGIZE_THIS(var)

static ELECTROCHEMICAL_DEV_KIT_cv_params   cv   = {0};
static ELECTROCHEMICAL_DEV_KIT_dpv_params  dpv  = {0};
static ELECTROCHEMICAL_DEV_KIT_ramp_params ramp = {0};

#define FLAGS_SIZE_TYPE uint16_t
#define FLAGS_TYPE      uint16_t

typedef struct
{
    const char **const    name;
    const FLAGS_SIZE_TYPE size;
    FLAGS_TYPE            flags;
} optarg_flags;

/** ==================== Run ==================== */
#define RUN_TABLE                                                              \
    X(cv, 0x01)                                                                \
    X(dpv, 0x02)                                                               \
    X(ramp, 0x04)

#define X(name, val) static const FLAGS_TYPE RUN_MASK_##name = val;
RUN_TABLE
#undef X

static const char *runs_name[] = {
#define X(name, val) #name,
    RUN_TABLE
#undef X
};

static optarg_flags runs = {
    .name  = runs_name,
    .size  = sizeof(runs_name) / sizeof(char *),
    .flags = 0,
};

/** ==================== Show ==================== */
#define SHOW_TABLE                                                             \
    X(attributes, 0x01)                                                        \
    X(results, 0x02)                                                           \
    X(structs, 0x04)

#define X(name, val) static const FLAGS_TYPE SHOW_MASK_##name = val;
SHOW_TABLE
#undef X

static const char *shows_name[] = {
#define X(name, val) #name,
    SHOW_TABLE
#undef X
};

static optarg_flags shows = {
    .name  = shows_name,
    .size  = sizeof(shows_name) / sizeof(char *),
    .flags = 0,
};

/** ==================== Print ==================== */

static void print_usage()
{
    // clang-format off
    printf("Usage:\n");
    printf("  %s [OPTIONS] --run <METHOD> --show <ITEMS> [PARAMETERS...]\n", program_invocation_name);
    printf("\n");

    printf("Options:\n");
    printf("  -h, --help                    Display the help message and exit\n");
    printf("      --run <METHOD>            Run a method (e.g., cv, dpv, ramp)\n");
    printf("      --show <ITEMS>            Show details (comma-separated: attributes,structs,results)\n");
    printf("      --[PARAMETERS] <VALUE>    Set parameter value\n");
    printf("\n");

    printf("Examples:\n");
    printf("  %s -h\n", program_invocation_name);
    printf("  %s --help\n", program_invocation_name);
    printf("  %s --run cv --show attributes,structs,results --e_begin 200 --e_step 9 --t_step 11 --n_step 3\n", program_invocation_name);
    printf("  %s --run cv --show attributes,structs,results --e_begin 200 --e_step 9 --e_vertex 300 --scan_rate 2\n", program_invocation_name);
    printf("  %s --run dpv --show attributes,structs,results --e_begin 200 --e_pulse 51 --e_step 9 --t_pulse 3 --t_step 8 --n_step 3\n", program_invocation_name);
    printf("  %s --run dpv --show attributes,structs,results --e_begin 200 --e_pulse 51 --e_step 9 --t_pulse 3 --e_end 300 --scan_rate 2\n", program_invocation_name);
    printf("  %s --run ramp --show attributes,structs,results --e_begin 200 --e_step 9 --t_step 11 --n_step 3\n", program_invocation_name);
    printf("  %s --run ramp --show attributes,structs,results --e_begin 200 --e_step 9 --e_end 300 --scan_rate 2\n", program_invocation_name);
    printf("\n");
    // clang-format on
}

static void print_help()
{
    // clang-format off
    printf("NOTE:\n");
    printf("  Use this demo to gain hands-on experience with the dev-kit.\n");
    printf("  Data type definitions in this demo:\n");
    printf("    ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE   %8s\n", STRINGIZE_THIS_DEFINITION(ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE));
    printf("    ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE    %8s\n", STRINGIZE_THIS_DEFINITION(ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE));
    printf("    ELECTROCHEMICAL_DEV_KIT_INDEX_TYPE     %8s\n", STRINGIZE_THIS_DEFINITION(ELECTROCHEMICAL_DEV_KIT_INDEX_TYPE));
    printf("    ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE    %8s\n", STRINGIZE_THIS_DEFINITION(ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE));
    printf("    ELECTROCHEMICAL_DEV_KIT_RATE_TYPE      %8s\n", STRINGIZE_THIS_DEFINITION(ELECTROCHEMICAL_DEV_KIT_RATE_TYPE));
    printf("    ELECTROCHEMICAL_DEV_KIT_TIME_TYPE      %8s\n", STRINGIZE_THIS_DEFINITION(ELECTROCHEMICAL_DEV_KIT_TIME_TYPE));
    printf("\n");

    print_usage();
    // clang-format on
}

static void print_structs(
    const char *const type_name,
    const char *const val_name,
    const void *const val,
    size_t            size
)
{
    printf("========== Structs ==========\n");
    printf("sizeof(%s): %ld\n", type_name, size);

    for (size_t i = 0; i < size; i++)
    {
        printf("%s[%ld]: %02x\n", type_name, i, ((uint8_t *)val)[i]);
    }

    printf("%s = *(%s*) (uint8_t[]) { ", val_name, type_name);
    for (size_t i = 0; i < size; i++)
    {
        printf("0x%02x, ", ((uint8_t *)val)[i]);
    }
    printf("};\n");

    printf("%s_hex_string: ", val_name);
    for (size_t i = 0; i < size; i++)
    {
        printf("%02x", ((uint8_t *)val)[i]);
    }
    printf("\n");
}

static void print_cv()
{
    printf("========== CV ==========\n");
    if (ELECTROCHEMICAL_DEV_KIT_cv_is_vaild(&cv) == false)
    {
        printf("CV is invalid.\n");
        return;
    }

    if (shows.flags & SHOW_MASK_structs)
    {
        print_structs(
            STRINGIZE_THIS(ELECTROCHEMICAL_DEV_KIT_cv_params),
            STRINGIZE_THIS(cv),
            &cv,
            sizeof(ELECTROCHEMICAL_DEV_KIT_cv_params)
        );
    }

    if (shows.flags & SHOW_MASK_attributes)
    {
        // clang-format off
        printf("========== Simple Attributes ==========\n");
        printf("e_begin: %d\n", cv.e_begin);
        printf("e_step: %d\n", cv.e_step);
        printf("n_step: %d\n", cv.n_step);
        printf("t_step: %d\n", cv.t_step);

        printf("========== Derived Attributes ==========\n");
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_vertex = ELECTROCHEMICAL_DEV_KIT_cv_get_e_vertex(&cv);
        printf("e_vertex: %d\n", e_vertex);
        ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE n_step_total = ELECTROCHEMICAL_DEV_KIT_cv_get_n_step_total(&cv);
        printf("n_step_total: %d\n", n_step_total);
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE scan_rate = ELECTROCHEMICAL_DEV_KIT_cv_get_scan_rate(&cv);
        printf("scan_rate: %f\n", scan_rate);
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_ramp = ELECTROCHEMICAL_DEV_KIT_cv_get_t_ramp(&cv);
        printf("t_ramp: %d\n", t_ramp);
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_total = ELECTROCHEMICAL_DEV_KIT_cv_get_t_total(&cv);
        printf("t_total: %d\n", t_total);
        // clang-format on
    }

    if (shows.flags & SHOW_MASK_results)
    {
        printf("========== Results ==========\n");
        ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE n_step_total =
            ELECTROCHEMICAL_DEV_KIT_cv_get_n_step_total(&cv);

        for (size_t i = 0; i < n_step_total; i++)
        {
            ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_at =
                ELECTROCHEMICAL_DEV_KIT_cv_get_e_at_index(&cv, i);
            printf("e_at[%ld]: %d\n", i, e_at);
        }
        for (size_t i = 0; i < n_step_total; i++)
        {
            ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_at =
                ELECTROCHEMICAL_DEV_KIT_cv_get_t_at_index(&cv, i);
            printf("t_at[%ld]: %d\n", i, t_at);
        }
    }
}

static void print_dpv()
{
    printf("========== DPV ==========\n");
    if (ELECTROCHEMICAL_DEV_KIT_dpv_is_vaild(&dpv) == false)
    {
        printf("DPV is invalid.\n");
        return;
    }

    if (shows.flags & SHOW_MASK_structs)
    {
        print_structs(
            STRINGIZE_THIS(dpv_params),
            STRINGIZE_THIS(dpv),
            &dpv,
            sizeof(ELECTROCHEMICAL_DEV_KIT_dpv_params)
        );
    }

    if (shows.flags & SHOW_MASK_attributes)
    {
        // clang-format off
        printf("========== Simple Attributes ==========\n");
        printf("e_begin: %d\n", dpv.e_begin);
        printf("e_pulse: %d\n", dpv.e_pulse);
        printf("e_step: %d\n", dpv.e_step);
        printf("t_pulse: %d\n", dpv.t_pulse);
        printf("t_step: %d\n", dpv.t_step);
        printf("n_step: %d\n", dpv.n_step);

        printf("========== Derived Attributes ==========\n");
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_end = ELECTROCHEMICAL_DEV_KIT_dpv_get_e_end(&dpv);
        printf("e_end: %d\n", e_end);
        ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE n_step_total = ELECTROCHEMICAL_DEV_KIT_dpv_get_n_step_total(&dpv);
        printf("n_step_total: %d\n", n_step_total);
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE scan_rate = ELECTROCHEMICAL_DEV_KIT_dpv_get_scan_rate(&dpv);
        printf("scan_rate: %f\n", scan_rate);
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_interval = ELECTROCHEMICAL_DEV_KIT_dpv_get_t_interval(&dpv);
        printf("t_interval: %d\n", t_interval);
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_total = ELECTROCHEMICAL_DEV_KIT_dpv_get_t_total(&dpv);
        printf("t_total: %d\n", t_total);
        // clang-format on
    }

    if (shows.flags & SHOW_MASK_results)
    {
        printf("========== Results ==========\n");
        ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE n_step_total =
            ELECTROCHEMICAL_DEV_KIT_dpv_get_n_step_total(&dpv);

        for (size_t i = 0; i < dpv.n_step; i++)
        {
            ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_at_pulse =
                ELECTROCHEMICAL_DEV_KIT_dpv_get_e_at_index(
                    &dpv,
                    i,
                    ELECTROCHEMICAL_DEV_KIT_dpv_selection_pulse
                );
            printf("e_at_pulse[%ld]: %d\n", i, e_at_pulse);
        }
        for (size_t i = 0; i < dpv.n_step; i++)
        {
            ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_at_step =
                ELECTROCHEMICAL_DEV_KIT_dpv_get_e_at_index(
                    &dpv,
                    i,
                    ELECTROCHEMICAL_DEV_KIT_dpv_selection_step
                );
            printf("e_at_step[%ld]: %d\n", i, e_at_step);
        }
        for (size_t i = 0; i < n_step_total; i++)
        {
            ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_at_step_pulse =
                ELECTROCHEMICAL_DEV_KIT_dpv_get_e_at_index(
                    &dpv,
                    i,
                    ELECTROCHEMICAL_DEV_KIT_dpv_selection_step_pulse
                );
            printf("e_at_step_pulse[%ld]: %d\n", i, e_at_step_pulse);
        }

        for (size_t i = 0; i < dpv.n_step; i++)
        {
            ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_at_pulse =
                ELECTROCHEMICAL_DEV_KIT_dpv_get_t_at_index(
                    &dpv,
                    i,
                    ELECTROCHEMICAL_DEV_KIT_dpv_selection_pulse
                );
            printf("t_at_pulse[%ld]: %d\n", i, t_at_pulse);
        }
        for (size_t i = 0; i < dpv.n_step; i++)
        {
            ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_at_step =
                ELECTROCHEMICAL_DEV_KIT_dpv_get_t_at_index(
                    &dpv,
                    i,
                    ELECTROCHEMICAL_DEV_KIT_dpv_selection_step
                );
            printf("t_at_step[%ld]: %d\n", i, t_at_step);
        }
        for (size_t i = 0; i < n_step_total; i++)
        {
            ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_at_step_pulse =
                ELECTROCHEMICAL_DEV_KIT_dpv_get_t_at_index(
                    &dpv,
                    i,
                    ELECTROCHEMICAL_DEV_KIT_dpv_selection_step_pulse
                );
            printf("t_at_step_pulse[%ld]: %d\n", i, t_at_step_pulse);
        }
    }
}

static void print_ramp()
{
    printf("========== Ramp ==========\n");
    if (ELECTROCHEMICAL_DEV_KIT_ramp_is_vaild(&ramp) == false)
    {
        printf("Ramp is invalid.\n");
        return;
    }

    if (shows.flags & SHOW_MASK_structs)
    {
        print_structs(
            STRINGIZE_THIS(ELECTROCHEMICAL_DEV_KIT_ramp_params),
            STRINGIZE_THIS(ramp),
            &ramp,
            sizeof(ELECTROCHEMICAL_DEV_KIT_ramp_params)
        );
    }

    if (shows.flags & SHOW_MASK_attributes)
    {
        // clang-format off
        printf("========== Simple Attributes ==========\n");
        printf("e_begin: %d\n", ramp.e_begin);
        printf("e_step: %d\n", ramp.e_step);
        printf("n_step: %d\n", ramp.n_step);
        printf("t_step: %d\n", ramp.t_step);

        printf("========== Derived Attributes ==========\n");
        ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_end = ELECTROCHEMICAL_DEV_KIT_ramp_get_e_end(&ramp);
        printf("e_end: %d\n", e_end);
        ELECTROCHEMICAL_DEV_KIT_RATE_TYPE scan_rate = ELECTROCHEMICAL_DEV_KIT_ramp_get_scan_rate(&ramp);
        printf("scan_rate: %f\n", scan_rate);
        ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_total = ELECTROCHEMICAL_DEV_KIT_ramp_get_t_total(&ramp);
        printf("t_total: %d\n", t_total);
        // clang-format on
    }

    if (shows.flags & SHOW_MASK_results)
    {
        printf("========== Results ==========\n");
        for (size_t i = 0; i < ramp.n_step; i++)
        {
            ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_at =
                ELECTROCHEMICAL_DEV_KIT_ramp_get_e_at_index(&ramp, i);
            printf("e_at[%ld]: %d\n", i, e_at);
        }
        for (size_t i = 0; i < ramp.n_step; i++)
        {
            ELECTROCHEMICAL_DEV_KIT_TIME_TYPE t_at =
                ELECTROCHEMICAL_DEV_KIT_ramp_get_t_at_index(&ramp, i);
            printf("t_at[%ld]: %d\n", i, t_at);
        }
    }
}

/** ==================== Main ==================== */
int main(int argc, char *argv[])
{
    int c;

    program_invocation_name = argv[0];

    if (argc < 2)
    {
        print_usage();
        return -1;
    }

    while (1)
    {
        int                  option_index   = 0;
        static struct option long_options[] = {
            {  "e_begin", required_argument, 0,   0},
            {    "e_end", required_argument, 0,   0},
            {  "e_pulse", required_argument, 0,   0},
            {   "e_step", required_argument, 0,   0},
            { "e_vertex", required_argument, 0,   0},
            {     "help",       no_argument, 0, 'h'},
            {   "n_step", required_argument, 0,   0},
            {      "run", required_argument, 0,   0},
            {"scan_rate", required_argument, 0,   0},
            {     "show", required_argument, 0,   0},
            {  "t_pulse", required_argument, 0,   0},
            {   "t_step", required_argument, 0,   0},
            {          0,                 0, 0,   0}
        };

        c = getopt_long(argc, argv, "h0", long_options, &option_index);
        if (c == -1)
            break;

        switch (c)
        {
            case 0:
                if (strcmp(long_options[option_index].name, "e_begin") == 0)
                {
                    cv.e_begin   = atoi(optarg);
                    dpv.e_begin  = atoi(optarg);
                    ramp.e_begin = atoi(optarg);
                }
                else if (strcmp(long_options[option_index].name, "e_end") == 0)
                {
                    ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_end = atoi(optarg);
                    ELECTROCHEMICAL_DEV_KIT_dpv_set_n_step_by_e_end(
                        &dpv,
                        e_end
                    );
                    ELECTROCHEMICAL_DEV_KIT_ramp_set_n_step_by_e_end(
                        &ramp,
                        e_end
                    );
                }
                else if (strcmp(long_options[option_index].name, "e_pulse") == 0)
                {
                    dpv.e_pulse = atoi(optarg);
                }
                else if (strcmp(long_options[option_index].name, "e_step") == 0)
                {
                    cv.e_step   = atoi(optarg);
                    dpv.e_step  = atoi(optarg);
                    ramp.e_step = atoi(optarg);
                }
                else if (strcmp(long_options[option_index].name, "e_vertex") == 0)
                {
                    ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE e_vertex = atoi(optarg);
                    ELECTROCHEMICAL_DEV_KIT_cv_set_n_step_by_e_vertex(
                        &cv,
                        e_vertex
                    );
                }
                else if (strcmp(long_options[option_index].name, "n_step") == 0)
                {
                    cv.n_step   = atoi(optarg);
                    dpv.n_step  = atoi(optarg);
                    ramp.n_step = atoi(optarg);
                }
                else if (strcmp(long_options[option_index].name, "run") == 0)
                {
                    const char *const delim = ",";
                    const char       *token = strtok(optarg, delim);

                    while (token != NULL)
                    {
                        for (size_t i = 0; i < runs.size; i++)
                        {
                            if (strcmp(token, runs.name[i]) == 0)
                            {
                                runs.flags |= 1 << i;
                            }
                        }
                        token = strtok(NULL, delim);
                    }
                }
                else if (strcmp(long_options[option_index].name, "scan_rate") == 0)
                {
                    ELECTROCHEMICAL_DEV_KIT_RATE_TYPE scan_rate = atof(optarg);
                    ELECTROCHEMICAL_DEV_KIT_cv_set_t_step_by_scan_rate(
                        &cv,
                        scan_rate
                    );
                    ELECTROCHEMICAL_DEV_KIT_dpv_set_t_step_by_scan_rate(
                        &dpv,
                        scan_rate
                    );
                    ELECTROCHEMICAL_DEV_KIT_ramp_set_t_step_by_scan_rate(
                        &ramp,
                        scan_rate
                    );
                }
                else if (strcmp(long_options[option_index].name, "show") == 0)
                {
                    const char *const delim = ",";
                    const char       *token = strtok(optarg, delim);

                    while (token != NULL)
                    {
                        for (size_t i = 0; i < shows.size; i++)
                        {
                            if (strcmp(token, shows.name[i]) == 0)
                            {
                                shows.flags |= 1 << i;
                            }
                        }
                        token = strtok(NULL, delim);
                    }
                }
                else if (strcmp(long_options[option_index].name, "t_pulse") == 0)
                {
                    dpv.t_pulse = atoi(optarg);
                }
                else if (strcmp(long_options[option_index].name, "t_step") == 0)
                {
                    cv.t_step   = atoi(optarg);
                    dpv.t_step  = atoi(optarg);
                    ramp.t_step = atoi(optarg);
                }
                else
                {
                    print_usage();
                    return -1;
                }
                break;

            case 'h':
                print_help();
                return 0;

            case '?':
                print_usage();
                return -1;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
                return -1;
        }
    }

    if (runs.flags & RUN_MASK_cv)
    {
        print_cv();
    }

    if (runs.flags & RUN_MASK_dpv)
    {
        print_dpv();
    }

    if (runs.flags & RUN_MASK_ramp)
    {
        print_ramp();
    }

    return 0;
}
