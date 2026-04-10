#include "electrochemical_dev_kit_cv.h"

extern inline ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE
ELECTROCHEMICAL_DEV_KIT_cv_get_e_at_index(
    const ELECTROCHEMICAL_DEV_KIT_cv_params *const p,
    ELECTROCHEMICAL_DEV_KIT_INDEX_TYPE             index
);
extern inline ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE
ELECTROCHEMICAL_DEV_KIT_cv_get_e_vertex(
    const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
);
extern inline ELECTROCHEMICAL_DEV_KIT_NUMBER_TYPE
ELECTROCHEMICAL_DEV_KIT_cv_get_n_step_total(
    const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
);
extern inline ELECTROCHEMICAL_DEV_KIT_RATE_TYPE
ELECTROCHEMICAL_DEV_KIT_cv_get_scan_rate(
    const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
);
extern inline ELECTROCHEMICAL_DEV_KIT_TIME_TYPE
ELECTROCHEMICAL_DEV_KIT_cv_get_t_at_index(
    const ELECTROCHEMICAL_DEV_KIT_cv_params *const p,
    ELECTROCHEMICAL_DEV_KIT_INDEX_TYPE             index
);
extern inline ELECTROCHEMICAL_DEV_KIT_TIME_TYPE
ELECTROCHEMICAL_DEV_KIT_cv_get_t_ramp(
    const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
);
extern inline ELECTROCHEMICAL_DEV_KIT_TIME_TYPE
ELECTROCHEMICAL_DEV_KIT_cv_get_t_total(
    const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
);
extern inline ELECTROCHEMICAL_DEV_KIT_BOOLEAN_TYPE
ELECTROCHEMICAL_DEV_KIT_cv_is_vaild(
    const ELECTROCHEMICAL_DEV_KIT_cv_params *const p
);
extern inline void ELECTROCHEMICAL_DEV_KIT_cv_set_n_step_by_e_vertex(
    ELECTROCHEMICAL_DEV_KIT_cv_params *const p,
    ELECTROCHEMICAL_DEV_KIT_ENERGY_TYPE      e_vertex
);
extern inline void ELECTROCHEMICAL_DEV_KIT_cv_set_t_step_by_scan_rate(
    ELECTROCHEMICAL_DEV_KIT_cv_params *const p,
    ELECTROCHEMICAL_DEV_KIT_RATE_TYPE        scan_rate
);
