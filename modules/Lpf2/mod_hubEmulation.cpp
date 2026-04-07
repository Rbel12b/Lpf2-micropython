#include "mod_types.h"

#define DEFINE_HUB_EMU_METHOD(name, method, fun_obj_def) LPF2_DEFINE_METHOD(hub_emulation_##name, method, fun_obj_def)
#define DEFINE_HUB_EMU_METHOD_VAR_BETWEEN(name, method, min_args, max_args) LPF2_DEFINE_METHOD_VAR_BETWEEN(hub_emulation_##name,  method, min_args, max_args)
#define GE_HUB_EMU_METHOD_OBJ(name) LPF2_GET_METHOD_OBJ(hub_emulation_##name)

#define SELF_TYPE mp_obj_lpf2_hub_emulation_t

extern "C" {

static mp_obj_t lpf2_hub_emulation_make_new(const mp_obj_type_t *type,
                                    size_t n_args,
                                    size_t n_kw,
                                    const mp_obj_t *args)
{

    SELF_TYPE *o = (SELF_TYPE*)m_malloc_with_finaliser(sizeof(SELF_TYPE));
    o->base.type = type;

    o->cpp_obj = new Lpf2::HubEmulation("Technic Hub", Lpf2::HubType::CONTROL_PLUS_HUB);
    o->owned = true;

    return MP_OBJ_FROM_PTR(o);
}

DEFINE_HUB_EMU_METHOD(start, (mp_obj_t self_in)
{
    GET_SELF_CPP()->start();
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_HUB_EMU_METHOD(stop, (mp_obj_t self_in)
{
    GET_SELF_CPP()->stop();
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_HUB_EMU_METHOD(set_use_built_in_devices, (mp_obj_t self_in, mp_obj_t use)
{
    GET_SELF_CPP()->setUseBuiltInDevices(mp_obj_is_true(use));
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_HUB_EMU_METHOD(set_battery_level, (mp_obj_t self_in, mp_obj_t level)
{
    GET_SELF_CPP()->setBatteryLevel(mp_obj_get_uint(level));
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_HUB_EMU_METHOD(set_battery_type, (mp_obj_t self_in, mp_obj_t type)
{
    GET_SELF_CPP()->setBatteryType((Lpf2::BatteryType)mp_obj_get_uint(type));
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_HUB_EMU_METHOD(set_name, (mp_obj_t self_in, mp_obj_t name)
{
    size_t len;
    auto cstr = mp_obj_str_get_data(name, &len);
    GET_SELF_CPP()->setName(std::string(cstr, len));
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_2);

// fw and hw version
// ---

DEFINE_HUB_EMU_METHOD(set_buton_state, (mp_obj_t self_in, mp_obj_t state)
{
    GET_SELF_CPP()->setButtonState((Lpf2::ButtonState)mp_obj_get_uint(state));
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_HUB_EMU_METHOD(set_alert, (mp_obj_t self_in, mp_obj_t alert, mp_obj_t on)
{
    GET_SELF_CPP()->setAlert((Lpf2::HubAlertType)mp_obj_get_uint(alert), mp_obj_is_true(on));
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_3);

DEFINE_HUB_EMU_METHOD(get_name, (mp_obj_t self_in)
{
    std::string s = GET_SELF_CPP()->getName();
    return mp_obj_new_str(s.c_str(), s.length());
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_HUB_EMU_METHOD(attach_port, (mp_obj_t self_in, mp_obj_t port_num, mp_obj_t port)
{
    if (!mp_obj_is_type(port, &lpf2_port_type) &&
        !mp_obj_is_subclass_fast(
            MP_OBJ_FROM_PTR(mp_obj_get_type(port)),
            MP_OBJ_FROM_PTR(&lpf2_port_type))) {
        mp_raise_TypeError(MP_ERROR_TEXT("expected Port"));
    }
    mp_obj_lpf2_port_t *port_obj = (mp_obj_lpf2_port_t*)MP_OBJ_TO_PTR(port);
    GET_SELF_CPP()->attachPort(mp_obj_get_uint(port_num), port_obj->cpp_obj);
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_3);

DEFINE_HUB_EMU_METHOD(del, (mp_obj_t self_in)
{
    auto self = GET_SELF();
    LPF2_LOG_V("Deleting HubEmulation, owner: %s", self->owned ? "true" : "false");
    if (self->owned && self->cpp_obj)
    {
        delete self->cpp_obj;
        self->cpp_obj = nullptr;
    }
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_1);

static const mp_rom_map_elem_t lpf2_hub_emulation_locals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___del__), MP_ROM_PTR(&GE_HUB_EMU_METHOD_OBJ(del))},
    {MP_ROM_QSTR(MP_QSTR_start), MP_ROM_PTR(&GE_HUB_EMU_METHOD_OBJ(start))},
    {MP_ROM_QSTR(MP_QSTR_stop), MP_ROM_PTR(&GE_HUB_EMU_METHOD_OBJ(stop))},
    {MP_ROM_QSTR(MP_QSTR_setUseBuiltInDevices), MP_ROM_PTR(&GE_HUB_EMU_METHOD_OBJ(set_use_built_in_devices))},
    {MP_ROM_QSTR(MP_QSTR_setBatteryLevel), MP_ROM_PTR(&GE_HUB_EMU_METHOD_OBJ(set_battery_level))},
    {MP_ROM_QSTR(MP_QSTR_setBatteryType), MP_ROM_PTR(&GE_HUB_EMU_METHOD_OBJ(set_battery_type))},
    {MP_ROM_QSTR(MP_QSTR_setName), MP_ROM_PTR(&GE_HUB_EMU_METHOD_OBJ(set_name))},
    {MP_ROM_QSTR(MP_QSTR_setButtonState), MP_ROM_PTR(&GE_HUB_EMU_METHOD_OBJ(set_buton_state))},
    {MP_ROM_QSTR(MP_QSTR_setAlert), MP_ROM_PTR(&GE_HUB_EMU_METHOD_OBJ(set_alert))},
    {MP_ROM_QSTR(MP_QSTR_getName), MP_ROM_PTR(&GE_HUB_EMU_METHOD_OBJ(get_name))},
    {MP_ROM_QSTR(MP_QSTR_attachPort), MP_ROM_PTR(&GE_HUB_EMU_METHOD_OBJ(attach_port))},
};

static MP_DEFINE_CONST_DICT(lpf2_hub_emulation_locals_dict, lpf2_hub_emulation_locals_table);

MP_DEFINE_CONST_OBJ_TYPE(
    lpf2_hub_emulation_type,
    MP_QSTR_hub_emulation,
    MP_TYPE_FLAG_NONE,
    make_new, (void*)lpf2_hub_emulation_make_new,
    locals_dict, &lpf2_hub_emulation_locals_dict
);

} // extern "C"