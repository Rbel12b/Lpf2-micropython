#include "mod_types.h"

#define DEFINE_VPORT_METHOD(name, method, fun_obj_def) LPF2_DEFINE_METHOD(virtual_port_##name, method, fun_obj_def)
#define DEFINE_VPORT_METHOD_VAR_BETWEEN(name, method, min_args, max_args) LPF2_DEFINE_METHOD_VAR_BETWEEN(virtual_port_##name,  method, min_args, max_args)
#define GET_VPORT_METHOD_OBJ(name) LPF2_GET_METHOD_OBJ(virtual_port_##name)

#define SELF_TYPE mp_obj_lpf2_virtual_port_t

extern "C" {

static mp_obj_t lpf2_virtual_port_make_new(const mp_obj_type_t *type,
                                    size_t n_args,
                                    size_t n_kw,
                                    const mp_obj_t *args)
{

    SELF_TYPE *o = (SELF_TYPE*)m_malloc_with_finaliser(sizeof(SELF_TYPE));
    o->base.type = type;

    o->cpp_obj = new Lpf2::Virtual::Port();
    o->owned = true;

    return MP_OBJ_FROM_PTR(o);
}

DEFINE_VPORT_METHOD(del, (mp_obj_t self_in)
{
    auto self = GET_SELF();
    LPF2_LOG_V("Deleting Virtual Port, owner: %s", self->owned ? "true" : "false");
    if (self->owned && self->cpp_obj)
    {
        delete self->cpp_obj;
        self->cpp_obj = nullptr;
    }
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_1);

static const mp_rom_map_elem_t lpf2_virtual_port_locals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___del__), MP_ROM_PTR(&GET_VPORT_METHOD_OBJ(del))},
    {MP_ROM_QSTR(MP_QSTR_update), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(update))},
    {MP_ROM_QSTR(MP_QSTR_writeData), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(write_data))},
    {MP_ROM_QSTR(MP_QSTR_startPower), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(start_power))},
    {MP_ROM_QSTR(MP_QSTR_setAccTime), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(set_acc_time))},
    {MP_ROM_QSTR(MP_QSTR_setDecTime), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(set_dec_time))},
    {MP_ROM_QSTR(MP_QSTR_startSpeed), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(start_speed))},
    {MP_ROM_QSTR(MP_QSTR_startSpeedForTime), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(start_speed_for_time))},
    {MP_ROM_QSTR(MP_QSTR_startSpeedForDegrees), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(start_speed_for_degrees))},
    {MP_ROM_QSTR(MP_QSTR_gotoAbsPosition), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(goto_abs_pos))},
    {MP_ROM_QSTR(MP_QSTR_presetEncoder), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(preset_encoder))},
    {MP_ROM_QSTR(MP_QSTR_setRgbColorIdx), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(set_rgb_color_idx))},
    {MP_ROM_QSTR(MP_QSTR_setRgbColor), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(set_rgb_color))},
    {MP_ROM_QSTR(MP_QSTR_setMode), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(set_mode))},
    {MP_ROM_QSTR(MP_QSTR_setModeCombo), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(set_mode_combo))},
    {MP_ROM_QSTR(MP_QSTR_isDeviceConnected), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(is_device_connected))},
    {MP_ROM_QSTR(MP_QSTR_getValue), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_value))},
    {MP_ROM_QSTR(MP_QSTR_getValueStr), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_value_str))},
    {MP_ROM_QSTR(MP_QSTR_getDeviceType), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_device_type))},
    {MP_ROM_QSTR(MP_QSTR_getModeCount), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_mode_count))},
    {MP_ROM_QSTR(MP_QSTR_getViewCount), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_view_count))},
    {MP_ROM_QSTR(MP_QSTR_getMode), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_mode))},
    {MP_ROM_QSTR(MP_QSTR_getModeComboCount), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_mode_combo_count))},
    {MP_ROM_QSTR(MP_QSTR_getModeCombo), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_mode_combo))},
    {MP_ROM_QSTR(MP_QSTR_getInputModes), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_input_modes))},
    {MP_ROM_QSTR(MP_QSTR_getOutputModes), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_output_modes))},
    {MP_ROM_QSTR(MP_QSTR_getCapabilities), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_capabilities))},
    {MP_ROM_QSTR(MP_QSTR_getInfoStr), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(get_info_str))},
    {MP_ROM_QSTR(MP_QSTR_speedToRaw), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(speed_to_raw))},
    {MP_ROM_QSTR(MP_QSTR_rawToSpeed), MP_ROM_PTR(&LPF2_GET_PORT_METHOD_OBJ(raw_to_speed))},
};

static MP_DEFINE_CONST_DICT(lpf2_virtual_port_locals_dict, lpf2_virtual_port_locals_table);

MP_DEFINE_CONST_OBJ_TYPE(
    lpf2_virtual_port_type,
    MP_QSTR_virtual_port,
    MP_TYPE_FLAG_NONE,
    make_new, (void*)lpf2_virtual_port_make_new,
    locals_dict, &lpf2_virtual_port_locals_dict
);
}