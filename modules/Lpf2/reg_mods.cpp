#include "mod_types.h"

extern "C" {
/* --- Local --- */
static const mp_rom_map_elem_t lpf2_local_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_Local) },
    { MP_ROM_QSTR(MP_QSTR_Port), MP_ROM_PTR(&lpf2_local_port_type) },
};

static MP_DEFINE_CONST_DICT(lpf2_local_globals, lpf2_local_globals_table);

const mp_obj_module_t lpf2_local_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&lpf2_local_globals,
};

/* --- Lpf2 --- */
static const mp_rom_map_elem_t lpf2_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_Lpf2) },
    { MP_ROM_QSTR(MP_QSTR_Port), MP_ROM_PTR(&lpf2_port_type) },
    { MP_ROM_QSTR(MP_QSTR_Local), MP_ROM_PTR(&lpf2_local_module) },
};

static MP_DEFINE_CONST_DICT(lpf2_globals, lpf2_globals_table);

extern "C" __attribute__((used))
const mp_obj_module_t lpf2_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&lpf2_globals,
};

MP_REGISTER_MODULE(MP_QSTR_Lpf2, lpf2_module);
} // extern "C"