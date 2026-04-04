extern "C" {
#include "py/runtime.h"
}

#include "mod_types.h"
#include "Port_tampoline.h"
#include "mp_bridge.h"

#define SELF_TYPE mp_obj_lpf2_port_t

extern "C" {
static mp_obj_t lpf2_port_make_new(const mp_obj_type_t *type,
                                    size_t n_args,
                                    size_t n_kw,
                                    const mp_obj_t *args)
{

    mp_obj_lpf2_port_t *o = m_new_obj(mp_obj_lpf2_port_t);
    o->base.type = type;

    // If instantiated directly or subclassed → create trampoline
    o->cpp_obj = new PortTrampoline(MP_OBJ_FROM_PTR(o));
    o->is_trampoline = true;

    return MP_OBJ_FROM_PTR(o);
}

static mp_obj_t lpf2_port_set_rgb_idx(mp_obj_t self_in, mp_obj_t idx_in)
{
    GET_SELF_CPP()->setRgbColorIdx((Lpf2::ColorIDX)mp_bridge_obj_get_int(idx_in));
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(lpf2_port_set_rgb_idx_obj, lpf2_port_set_rgb_idx);

static mp_obj_t lpf2_port_get_mode_count(mp_obj_t self_in)
{
    return mp_bridge_obj_new_int(GET_SELF_CPP()->getModeCount());
}
static MP_DEFINE_CONST_FUN_OBJ_1(lpf2_port_get_mode_count_obj, lpf2_port_get_mode_count);

static mp_obj_t lpf2_port_get_device_type(mp_obj_t self_in)
{
    return mp_bridge_obj_new_int((int)GET_SELF_CPP()->getDeviceType());
}
static MP_DEFINE_CONST_FUN_OBJ_1(lpf2_port_get_device_type_obj, lpf2_port_get_device_type);

static const mp_rom_map_elem_t lpf2_port_locals_table[] = {
    {MP_ROM_QSTR(MP_QSTR_setRgbColorIdx), MP_ROM_PTR(&lpf2_port_set_rgb_idx_obj)},
    {MP_ROM_QSTR(MP_QSTR_getModeCount), MP_ROM_PTR(&lpf2_port_get_mode_count_obj)},
    {MP_ROM_QSTR(MP_QSTR_getDeviceType), MP_ROM_PTR(&lpf2_port_get_device_type_obj)},
};

static MP_DEFINE_CONST_DICT(lpf2_port_locals_dict, lpf2_port_locals_table);

MP_DEFINE_CONST_OBJ_TYPE(
    lpf2_port_type, 
    MP_QSTR_Port,
    MP_TYPE_FLAG_NONE,
    make_new, (void*)lpf2_port_make_new,
    locals_dict, &lpf2_port_locals_dict
);
} // extern "C"