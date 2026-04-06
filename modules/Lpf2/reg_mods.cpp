#include "mod_types.h"

extern "C" {

/* --- Lpf2.Color --- */
#define LPF2_REG_COLOR(name) { MP_ROM_QSTR(MP_QSTR_##name), MP_ROM_INT((uint8_t)Lpf2::ColorIDX::name) }
static const mp_rom_map_elem_t lpf2_color_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_color) },
    LPF2_REG_COLOR(BLACK),
    LPF2_REG_COLOR(PINK),
    LPF2_REG_COLOR(PURPLE),
    LPF2_REG_COLOR(BLUE),
    LPF2_REG_COLOR(LIGHTBLUE),
    LPF2_REG_COLOR(CYAN),
    LPF2_REG_COLOR(GREEN),
    LPF2_REG_COLOR(YELLOW),
    LPF2_REG_COLOR(ORANGE),
    LPF2_REG_COLOR(RED),
    LPF2_REG_COLOR(WHITE),
    LPF2_REG_COLOR(NUM_COLORS),
    LPF2_REG_COLOR(NONE),
};

static MP_DEFINE_CONST_DICT(lpf2_color_globals, lpf2_color_globals_table);

const mp_obj_module_t lpf2_color_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&lpf2_color_globals,
};

/* --- Lpf2.Local --- */
static const mp_rom_map_elem_t lpf2_local_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_local) },
    { MP_ROM_QSTR(MP_QSTR_port), MP_ROM_PTR(&lpf2_local_port_type) },
};

static MP_DEFINE_CONST_DICT(lpf2_local_globals, lpf2_local_globals_table);

const mp_obj_module_t lpf2_local_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&lpf2_local_globals,
};

/* --- Lpf2 --- */
static const mp_rom_map_elem_t lpf2_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_lpf2) },
    { MP_ROM_QSTR(MP_QSTR_port), MP_ROM_PTR(&lpf2_port_type) },
    { MP_ROM_QSTR(MP_QSTR_local), MP_ROM_PTR(&lpf2_local_module) },
    { MP_ROM_QSTR(MP_QSTR_mode), MP_ROM_PTR(&lpf2_mode_type) },
    { MP_ROM_QSTR(MP_QSTR_color), MP_ROM_PTR(&lpf2_color_module) },
};

static MP_DEFINE_CONST_DICT(lpf2_globals, lpf2_globals_table);

extern "C" __attribute__((used))
const mp_obj_module_t lpf2_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&lpf2_globals,
};

MP_REGISTER_MODULE(MP_QSTR_lpf2, lpf2_module);
} // extern "C"