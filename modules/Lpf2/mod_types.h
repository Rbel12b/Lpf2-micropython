extern "C" {
#include "py/runtime.h"
}

#define GET_SELF() ((SELF_TYPE*)(MP_OBJ_TO_PTR(self_in)))
#define GET_SELF_CPP() (GET_SELF()->cpp_obj)

#include "Lpf2/Port.hpp"
#include "Lpf2/Local/Port.hpp"
#include "Lpf2/LWPConst.hpp"
#include "Lpf2/Virtual/Port.hpp"
#include "Lpf2/HubEmulation.hpp"

#define LPF2_DEFINE_METHOD(name, method, fun_obj_def) \
    static mp_obj_t lpf2_##name method \
    fun_obj_def(lpf2_##name##_obj, lpf2_##name);

#define LPF2_DEFINE_METHOD_VAR_BETWEEN(name, method, min_args, max_args) \
    static mp_obj_t lpf2_##name(size_t n_args, const mp_obj_t *args) method \
    MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lpf2_##name##_obj, min_args, max_args, lpf2_##name);

#define LPF2_GET_METHOD_OBJ(name) lpf2_##name##_obj

#define LPF2_REG(str, name) { MP_ROM_QSTR(MP_QSTR_##str), MP_ROM_INT((uint8_t)name) }
#define LPF2_DEFINE_CONST_DICT(name) MP_DEFINE_CONST_DICT(lpf2_##name##_globals, lpf2_##name##_globals_table)
#define LPF2_DEFINE_MOD(name) \
    const mp_obj_module_t lpf2_##name##_module = { \
        .base = { &mp_type_module }, \
        .globals = (mp_obj_dict_t*)&lpf2_##name##_globals, \
    }

#define LPF2_DEFINE_GLOB_TABLE(name, ...) \
    const mp_rom_map_elem_t lpf2_##name##_globals_table[] = { \
        { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_##name) }, \
        __VA_ARGS__ \
    }

#define LPF2_DEFINE_GLOB_TABLE_DICT(name, ...) \
    static LPF2_DEFINE_GLOB_TABLE(name, __VA_ARGS__); \
    static LPF2_DEFINE_CONST_DICT(name)

#define LPF2_DEFINE_MOD_WITH_GLOB(name, ...) \
    LPF2_DEFINE_GLOB_TABLE_DICT(name, __VA_ARGS__); \
    LPF2_DEFINE_MOD(name)

#define LPF2_DEFINE_MOD_WITH_GLOB_STATIC(name, ...) \
    LPF2_DEFINE_GLOB_TABLE_DICT(name, __VA_ARGS__); \
    static LPF2_DEFINE_MOD(name)

#define LPF2_DEFINE_MOD_WITH_GLOB_ATTR_USED(name, ...) \
    LPF2_DEFINE_GLOB_TABLE_DICT(name, __VA_ARGS__); \
    extern "C" __attribute__((used)) \
    LPF2_DEFINE_MOD(name)

#define LPF2_MOD_EXTERN(name) extern const mp_obj_module_t lpf2_##name##_module
#define LPF2_GET_MOD(name) lpf2_##name##_module

#define LPF2_GET_LPF2_MOD_REG(name) { MP_ROM_QSTR(MP_QSTR_##name), MP_ROM_PTR(&lpf2_##name##_module) }
#define LPF2_GET_LPF2_TYPE_REG(name) { MP_ROM_QSTR(MP_QSTR_##name), MP_ROM_PTR(&lpf2_##name##_type) }

#define LPF2_GET_PORT_METHOD_OBJ(name) LPF2_GET_METHOD_OBJ(port_##name)
#define LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(name) extern const mp_obj_fun_builtin_fixed_t LPF2_GET_PORT_METHOD_OBJ(name)
#define LPF2_DEFINE_PORT_METHOD_VAR_OBJ_EXTERN(name) extern const mp_obj_fun_builtin_var_t LPF2_GET_PORT_METHOD_OBJ(name)

extern "C" {

typedef struct _mp_obj_lpf2_port_t
{
    mp_obj_base_t base;
    Lpf2::Port *cpp_obj = nullptr;
    bool owned = false; // if true cpp_obj is owned by the mp obj
    bool is_trampoline = false;
} mp_obj_lpf2_port_t;
extern const mp_obj_type_t lpf2_port_type;
extern const mp_obj_type_t lpf2_local_port_type;

typedef struct _mp_obj_lpf2_virtual_port_t
{
    mp_obj_base_t base;
    Lpf2::Virtual::Port *cpp_obj = nullptr;
    bool owned = false; // if true cpp_obj is owned by the mp obj
    bool is_trampoline = false;
} mp_obj_lpf2_virtual_port_t;
extern const mp_obj_type_t lpf2_virtual_port_type;

typedef struct _mp_obj_lpf2_mode_t
{
    mp_obj_base_t base;
    Lpf2::Mode *cpp_obj = nullptr;
    bool owned = false; // if true cpp_obj is owned by the mp obj
} mp_obj_lpf2_mode_t;
extern const mp_obj_type_t lpf2_mode_type;
typedef struct _mp_obj_lpf2_version_t
{
    mp_obj_base_t base;
    Lpf2::Version*cpp_obj = nullptr;
    bool owned = false; // if true cpp_obj is owned by the mp obj
} mp_obj_lpf2_version_t;
extern const mp_obj_type_t lpf2_version_type;

typedef struct _mp_obj_lpf2_hub_emulation_t
{
    mp_obj_base_t base;
    Lpf2::HubEmulation *cpp_obj = nullptr;
    bool owned = false; // if true cpp_obj is owned by the mp obj
} mp_obj_lpf2_hub_emulation_t;
extern const mp_obj_type_t lpf2_hub_emulation_type;

LPF2_MOD_EXTERN(color);
LPF2_MOD_EXTERN(hub_type);
LPF2_MOD_EXTERN(device_type);
LPF2_MOD_EXTERN(battery_type);
LPF2_MOD_EXTERN(alerts);
LPF2_MOD_EXTERN(button_state);
LPF2_MOD_EXTERN(port_num);

LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(update);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(write_data);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(start_power);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(set_acc_time);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(set_dec_time);
LPF2_DEFINE_PORT_METHOD_VAR_OBJ_EXTERN(start_speed);
LPF2_DEFINE_PORT_METHOD_VAR_OBJ_EXTERN(start_speed_for_time);
LPF2_DEFINE_PORT_METHOD_VAR_OBJ_EXTERN(start_speed_for_degrees);
LPF2_DEFINE_PORT_METHOD_VAR_OBJ_EXTERN(goto_abs_pos);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(preset_encoder);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(set_rgb_color_idx);
LPF2_DEFINE_PORT_METHOD_VAR_OBJ_EXTERN(set_rgb_color);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(set_mode);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(set_mode_combo);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(is_device_connected);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_value);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_value_str);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_device_type);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_mode_count);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_view_count);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_mode);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_mode_combo_count);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_mode_combo);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_input_modes);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_output_modes);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_capabilities);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(get_info_str);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(speed_to_raw);
LPF2_DEFINE_PORT_METHOD_OBJ_EXTERN(raw_to_speed);

} // extern "C"