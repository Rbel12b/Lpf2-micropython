extern "C" {
#include "py/runtime.h"
}

#define GET_SELF() ((SELF_TYPE*)(MP_OBJ_TO_PTR(self_in)))
#define GET_SELF_CPP() (GET_SELF()->cpp_obj)

#include "Lpf2/Port.hpp"
#include "Lpf2/Local/Port.hpp"
#include "Lpf2/LWPConst.hpp"

#define LPF2_DEFINE_METHOD(name, method, fun_obj_def) \
    static mp_obj_t lpf2_##name method \
    static fun_obj_def(lpf2_##name##_obj, lpf2_##name);

#define LPF2_DEFINE_METHOD_VAR_BETWEEN(name, method, min_args, max_args) \
    static mp_obj_t lpf2_##name(size_t n_args, const mp_obj_t *args) method \
    static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(lpf2_##name##_obj, min_args, max_args, lpf2_##name);

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

#define LPF2_DEFINE_MOD_WITH_GLOB_ATTR_USED(name, ...) \
    LPF2_DEFINE_GLOB_TABLE_DICT(name, __VA_ARGS__); \
    extern "C" __attribute__((used)) \
    LPF2_DEFINE_MOD(name)

#define LPF2_MOD_EXTERN(name) extern const mp_obj_module_t lpf2_##name##_module
#define LPF2_GET_MOD(name) lpf2_##name##_module

#define LPF2_GET_LPF2_MOD_REG(name) { MP_ROM_QSTR(MP_QSTR_##name), MP_ROM_PTR(&lpf2_##name##_module) }
#define LPF2_GET_LPF2_TYPE_REG(name) { MP_ROM_QSTR(MP_QSTR_##name), MP_ROM_PTR(&lpf2_##name##_type) }

extern "C" {

typedef struct _mp_obj_lpf2_port_t
{
    mp_obj_base_t base;
    Lpf2::Port *cpp_obj = nullptr;
    bool owned = false; // owned by the mp obj
    bool is_trampoline = false;
} mp_obj_lpf2_port_t;
extern const mp_obj_type_t lpf2_port_type;
extern const mp_obj_type_t lpf2_local_port_type;

typedef struct _mp_obj_lpf2_mode_t
{
    mp_obj_base_t base;
    Lpf2::Mode *cpp_obj = nullptr;
    bool owned = false; // owned by the mp obj
} mp_obj_lpf2_mode_t;
extern const mp_obj_type_t lpf2_mode_type;

LPF2_MOD_EXTERN(color);
LPF2_MOD_EXTERN(hub_type);
LPF2_MOD_EXTERN(device_type);

} // extern "C"