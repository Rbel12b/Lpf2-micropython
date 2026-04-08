#include "mod_types.h"

extern "C" {

/* --- lpf2.local --- */
LPF2_DEFINE_MOD_WITH_GLOB(local,
    { MP_ROM_QSTR(MP_QSTR_port), MP_ROM_PTR(&lpf2_local_port_type) }
);

/* --- lpf2.virtual --- */
LPF2_DEFINE_MOD_WITH_GLOB(virtual,
    { MP_ROM_QSTR(MP_QSTR_port), MP_ROM_PTR(&lpf2_virtual_port_type) }
);

/* --- lpf2 --- */
LPF2_DEFINE_MOD_WITH_GLOB_ATTR_USED(lpf2,
    LPF2_GET_LPF2_MOD_REG(hub_type),
    LPF2_GET_LPF2_MOD_REG(device_type),
    LPF2_GET_LPF2_MOD_REG(alerts),
    LPF2_GET_LPF2_MOD_REG(battery_type),
    LPF2_GET_LPF2_MOD_REG(button_state),
    LPF2_GET_LPF2_MOD_REG(color),
    LPF2_GET_LPF2_MOD_REG(port_num),
    LPF2_GET_LPF2_MOD_REG(local),
    LPF2_GET_LPF2_MOD_REG(virtual),
    LPF2_GET_LPF2_TYPE_REG(port),
    LPF2_GET_LPF2_TYPE_REG(mode),
    LPF2_GET_LPF2_TYPE_REG(version),
    LPF2_GET_LPF2_TYPE_REG(hub_emulation),
);

MP_REGISTER_MODULE(MP_QSTR_lpf2, LPF2_GET_MOD(lpf2));
} // extern "C"