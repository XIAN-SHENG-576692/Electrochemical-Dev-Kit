#include "electrochemical.h"

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

#define ENERGY_TYPE int16_t
#define INDEX_TYPE  uint8_t
#define NUM_TYPE    uint8_t
#define RATE_TYPE   float
#define TIME_TYPE   uint16_t

DECLARE_ELECTROCHEMICAL_CV(
    cv,
    ENERGY_TYPE,
    INDEX_TYPE,
    NUM_TYPE,
    RATE_TYPE,
    TIME_TYPE
)
DECLARE_ELECTROCHEMICAL_DPV(
    dpv,
    ENERGY_TYPE,
    INDEX_TYPE,
    NUM_TYPE,
    RATE_TYPE,
    TIME_TYPE
)
DECLARE_ELECTROCHEMICAL_RAMP(
    ramp,
    ENERGY_TYPE,
    INDEX_TYPE,
    NUM_TYPE,
    RATE_TYPE,
    TIME_TYPE
)

static cv_params   cv   = {0};
static dpv_params  dpv  = {0};
static ramp_params ramp = {0};

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
    printf("  %s --run dpv --show attributes,structs,results --e_begin 200 --e_pulse 51 --e_step 9 --t_pulse 8 --t_step 3 --n_step 3\n", program_invocation_name);
    printf("  %s --run ramp --show attributes,structs,results --e_begin 200 --e_step 9 --t_step 11 --n_step 3\n", program_invocation_name);
    printf("\n");
    // clang-format on
}

static void print_help()
{
    // clang-format off
    printf("NOTE:\n");
    printf("  Use this demo to gain hands-on experience with the dev-kit.\n");
    printf("  Data type definitions in this demo:\n");
    printf("    ENERGY_TYPE    %8s\n", STRINGIZE_THIS_DEFINITION(ENERGY_TYPE));
    printf("    INDEX_TYPE     %8s\n", STRINGIZE_THIS_DEFINITION(INDEX_TYPE));
    printf("    NUM_TYPE       %8s\n", STRINGIZE_THIS_DEFINITION(NUM_TYPE));
    printf("    RATE_TYPE      %8s\n", STRINGIZE_THIS_DEFINITION(RATE_TYPE));
    printf("    TIME_TYPE      %8s\n", STRINGIZE_THIS_DEFINITION(TIME_TYPE));
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
    if (shows.flags & SHOW_MASK_structs)
    {
        print_structs(
            STRINGIZE_THIS(cv_params),
            STRINGIZE_THIS(cv),
            &cv,
            sizeof(cv_params)
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
        ENERGY_TYPE e_vertex = cv_get_e_vertex(&cv);
        printf("e_vertex: %d\n", e_vertex);
        NUM_TYPE n_step_total = cv_get_n_step_total(&cv);
        printf("n_step_total: %d\n", n_step_total);
        RATE_TYPE scan_rate = cv_get_scan_rate(&cv);
        printf("scan_rate: %f\n", scan_rate);
        TIME_TYPE t_ramp = cv_get_t_ramp(&cv);
        printf("t_ramp: %d\n", t_ramp);
        TIME_TYPE t_total = cv_get_t_total(&cv);
        printf("t_total: %d\n", t_total);
        // clang-format on
    }

    if (shows.flags & SHOW_MASK_results)
    {
        printf("========== Results ==========\n");
        NUM_TYPE n_step_total = cv_get_n_step_total(&cv);

        for (size_t i = 0; i < n_step_total; i++)
        {
            ENERGY_TYPE e_energy = cv_get_energy_by_index(&cv, i);
            printf("e_energy[%ld]: %d\n", i, e_energy);
        }
        for (size_t i = 0; i < n_step_total; i++)
        {
            TIME_TYPE t_time = cv_get_time_by_index(&cv, i);
            printf("t_time[%ld]: %d\n", i, t_time);
        }
    }
}

static void print_dpv()
{
    printf("========== DPV ==========\n");
    if (shows.flags & SHOW_MASK_structs)
    {
        print_structs(
            STRINGIZE_THIS(dpv_params),
            STRINGIZE_THIS(dpv),
            &dpv,
            sizeof(dpv_params)
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
        ENERGY_TYPE e_end = dpv_get_e_end(&dpv);
        printf("e_end: %d\n", e_end);
        NUM_TYPE n_step_total = dpv_get_n_step_total(&dpv);
        printf("n_step_total: %d\n", n_step_total);
        RATE_TYPE scan_rate = dpv_get_scan_rate(&dpv);
        printf("scan_rate: %f\n", scan_rate);
        TIME_TYPE t_interval = dpv_get_t_interval(&dpv);
        printf("t_interval: %d\n", t_interval);
        TIME_TYPE t_total = dpv_get_t_total(&dpv);
        printf("t_total: %d\n", t_total);
        // clang-format on
    }

    if (shows.flags & SHOW_MASK_results)
    {
        printf("========== Results ==========\n");
        NUM_TYPE n_step_total = dpv_get_n_step_total(&dpv);

        for (size_t i = 0; i < n_step_total; i++)
        {
            ENERGY_TYPE e_energy_all = dpv_get_energy_by_index(
                &dpv,
                i,
                ELECTROCHEMICAL_DPV_SELECTION_ALL
            );
            printf("e_energy_all[%ld]: %d\n", i, e_energy_all);
        }
        for (size_t i = 0; i < dpv.n_step; i++)
        {
            ENERGY_TYPE e_energy_pulse = dpv_get_energy_by_index(
                &dpv,
                i,
                ELECTROCHEMICAL_DPV_SELECTION_PULSE
            );
            printf("e_energy_pulse[%ld]: %d\n", i, e_energy_pulse);
        }
        for (size_t i = 0; i < dpv.n_step; i++)
        {
            ENERGY_TYPE e_energy_step = dpv_get_energy_by_index(
                &dpv,
                i,
                ELECTROCHEMICAL_DPV_SELECTION_STEP
            );
            printf("e_energy_step[%ld]: %d\n", i, e_energy_step);
        }

        for (size_t i = 0; i < n_step_total; i++)
        {
            TIME_TYPE t_time_all = dpv_get_time_by_index(
                &dpv,
                i,
                ELECTROCHEMICAL_DPV_SELECTION_ALL
            );
            printf("t_time_all[%ld]: %d\n", i, t_time_all);
        }
        for (size_t i = 0; i < dpv.n_step; i++)
        {
            TIME_TYPE t_time_pulse = dpv_get_time_by_index(
                &dpv,
                i,
                ELECTROCHEMICAL_DPV_SELECTION_PULSE
            );
            printf("t_time_pulse[%ld]: %d\n", i, t_time_pulse);
        }
        for (size_t i = 0; i < dpv.n_step; i++)
        {
            TIME_TYPE t_time_step = dpv_get_time_by_index(
                &dpv,
                i,
                ELECTROCHEMICAL_DPV_SELECTION_STEP
            );
            printf("t_time_step[%ld]: %d\n", i, t_time_step);
        }
    }
}

static void print_ramp()
{
    printf("========== Ramp ==========\n");
    if (shows.flags & SHOW_MASK_structs)
    {
        print_structs(
            STRINGIZE_THIS(ramp_params),
            STRINGIZE_THIS(ramp),
            &ramp,
            sizeof(ramp_params)
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
        ENERGY_TYPE e_end = ramp_get_e_end(&ramp);
        printf("e_end: %d\n", e_end);
        RATE_TYPE scan_rate = ramp_get_scan_rate(&ramp);
        printf("scan_rate: %f\n", scan_rate);
        TIME_TYPE t_total = ramp_get_t_total(&ramp);
        printf("t_total: %d\n", t_total);
        // clang-format on
    }

    if (shows.flags & SHOW_MASK_results)
    {
        printf("========== Results ==========\n");
        for (size_t i = 0; i < ramp.n_step; i++)
        {
            ENERGY_TYPE e_energy = ramp_get_energy_by_index(&ramp, i);
            printf("e_energy[%ld]: %d\n", i, e_energy);
        }
        for (size_t i = 0; i < ramp.n_step; i++)
        {
            TIME_TYPE t_time = ramp_get_time_by_index(&ramp, i);
            printf("t_time[%ld]: %d\n", i, t_time);
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
            {"e_begin", required_argument, 0,   0},
            {"e_pulse", required_argument, 0,   0},
            { "e_step", required_argument, 0,   0},
            { "n_step", required_argument, 0,   0},
            {"t_pulse", required_argument, 0,   0},
            { "t_step", required_argument, 0,   0},
            {   "help",       no_argument, 0, 'h'},
            {    "run", required_argument, 0,   0},
            {   "show", required_argument, 0,   0},
            {        0,                 0, 0,   0}
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
                else if (strcmp(long_options[option_index].name, "n_step") == 0)
                {
                    cv.n_step   = atoi(optarg);
                    dpv.n_step  = atoi(optarg);
                    ramp.n_step = atoi(optarg);
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
