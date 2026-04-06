#include "mod_types.h"

extern "C" {

/* --- lpf2.Local --- */
LPF2_DEFINE_MOD_WITH_GLOB(local,
    { MP_ROM_QSTR(MP_QSTR_port), MP_ROM_PTR(&lpf2_local_port_type) }
);

/* --- lpf2 --- */
LPF2_DEFINE_MOD_WITH_GLOB_ATTR_USED(lpf2,
    LPF2_GET_LPF2_MOD_REG(hub_type),
    LPF2_GET_LPF2_MOD_REG(color),
    LPF2_GET_LPF2_MOD_REG(local),
    LPF2_GET_LPF2_TYPE_REG(port),
    LPF2_GET_LPF2_TYPE_REG(mode)
);

MP_REGISTER_MODULE(MP_QSTR_lpf2, LPF2_GET_MOD(lpf2));
} // extern "C"