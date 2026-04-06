extern "C" {
#include "py/runtime.h"
}

#include "mod_types.h"
#include "Port_tampoline.h"

#define SELF_TYPE mp_obj_lpf2_port_t

extern "C" {
static mp_obj_t lpf2_port_make_new(const mp_obj_type_t *type,
                                    size_t n_args,
                                    size_t n_kw,
                                    const mp_obj_t *args)
{

    mp_obj_lpf2_port_t *o = (mp_obj_lpf2_port_t*)m_malloc_with_finaliser(sizeof(mp_obj_lpf2_port_t));
    o->base.type = type;

    o->cpp_obj = new PortTrampoline(MP_OBJ_FROM_PTR(o));
    o->is_trampoline = true;
    o->owned = true;

    return MP_OBJ_FROM_PTR(o);
}

#define DEFINE_PORT_METHOD(name, method, fun_obj_def) LPF2_DEFINE_METHOD(port_##name, method, fun_obj_def)

#define DEFINE_PORT_METHOD_VAR_BETWEEN(name, method, min_args, max_args) LPF2_DEFINE_METHOD_VAR_BETWEEN(port_##name,  method, min_args, max_args)

#define GET_PORT_METHOD_OBJ(name) LPF2_GET_METHOD_OBJ(port_##name)

DEFINE_PORT_METHOD(write_data, (mp_obj_t self_in,
                                           mp_obj_t mode_in,
                                           mp_obj_t buf_in) {
    mp_buffer_info_t buf;
    mp_get_buffer_raise(buf_in, &buf, MP_BUFFER_READ);

    std::vector<uint8_t> data(
        (uint8_t*)buf.buf,
        (uint8_t*)buf.buf + buf.len
    );

    int ret = GET_SELF_CPP()->writeData(
        mp_obj_get_int(mode_in),
        data
    );

    return mp_obj_new_int(ret);
},
MP_DEFINE_CONST_FUN_OBJ_3);

DEFINE_PORT_METHOD(start_power, (mp_obj_t self_in, mp_obj_t pw)
{
    GET_SELF_CPP()->startPower(mp_obj_get_int(pw));
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_PORT_METHOD(set_acc_time, (mp_obj_t self_in, mp_obj_t time, mp_obj_t profile)
{
    GET_SELF_CPP()->setAccTime(mp_obj_get_int(time), (Lpf2::AccelerationProfile)mp_obj_get_int(profile));
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_3);

DEFINE_PORT_METHOD(set_dec_time, (mp_obj_t self_in, mp_obj_t time, mp_obj_t profile)
{
    GET_SELF_CPP()->setDecTime(mp_obj_get_int(time), (Lpf2::AccelerationProfile)mp_obj_get_int(profile));
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_3);

DEFINE_PORT_METHOD_VAR_BETWEEN(start_speed,
{
    void *self_in = MP_OBJ_TO_PTR(args[0]);

    int8_t speed       = (int8_t)  mp_obj_get_int(args[1]);
    uint8_t maxPower   = (uint8_t) mp_obj_get_int(args[2]);
    uint8_t useProfile = 0;
    if (n_args > 3) {
        useProfile = (uint8_t) mp_obj_get_int(args[3]);
    }
    GET_SELF_CPP()->startSpeed(speed, maxPower, useProfile);
    return mp_const_none;
},
3, 4);

DEFINE_PORT_METHOD_VAR_BETWEEN(start_speed_for_time,
{
    void *self_in = MP_OBJ_TO_PTR(args[0]);
    
    uint16_t time      = (uint16_t) mp_obj_get_int(args[1]);
    int8_t speed       = (int8_t)  mp_obj_get_int(args[2]);
    uint8_t maxPower   = (uint8_t) mp_obj_get_int(args[3]);
    Lpf2::BrakingStyle endState = (Lpf2::BrakingStyle) mp_obj_get_int(args[4]);

    uint8_t useProfile = 0;
    if (n_args > 5) {
        useProfile = (uint8_t) mp_obj_get_int(args[5]);
    }

    GET_SELF_CPP()->startSpeedForTime(time, speed, maxPower, endState, useProfile);
    return mp_const_none;
},
4, 5);

DEFINE_PORT_METHOD_VAR_BETWEEN(start_speed_for_degrees,
{
    void *self_in = MP_OBJ_TO_PTR(args[0]);
    
    uint16_t degrees   = (uint32_t) mp_obj_get_int(args[1]);
    int8_t speed       = (int8_t)  mp_obj_get_int(args[2]);
    uint8_t maxPower   = (uint8_t) mp_obj_get_int(args[3]);
    Lpf2::BrakingStyle endState = (Lpf2::BrakingStyle) mp_obj_get_int(args[4]);

    uint8_t useProfile = 0;
    if (n_args > 5) {
        useProfile = (uint8_t) mp_obj_get_int(args[5]);
    }

    GET_SELF_CPP()->startSpeedForDegrees(degrees, speed, maxPower, endState, useProfile);
    return mp_const_none;
},
4, 5);

DEFINE_PORT_METHOD_VAR_BETWEEN(goto_abs_pos,
{
    void *self_in = MP_OBJ_TO_PTR(args[0]);
    
    uint16_t absPos    = (int32_t) mp_obj_get_int(args[1]);
    uint8_t speed      = (uint8_t) mp_obj_get_int(args[2]);
    uint8_t maxPower   = (uint8_t) mp_obj_get_int(args[3]);
    Lpf2::BrakingStyle endState = (Lpf2::BrakingStyle) mp_obj_get_int(args[4]);

    uint8_t useProfile = 0;
    if (n_args > 5) {
        useProfile = (uint8_t) mp_obj_get_int(args[5]);
    }

    GET_SELF_CPP()->gotoAbsPosition(absPos, speed, maxPower, endState, useProfile);
    return mp_const_none;
},
4, 5);

DEFINE_PORT_METHOD(preset_encoder, (mp_obj_t self_in, mp_obj_t pos)
{
    GET_SELF_CPP()->presetEncoder(mp_obj_get_int(pos));
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_PORT_METHOD(set_rgb_color_idx, (mp_obj_t self_in, mp_obj_t idx)
{
    GET_SELF_CPP()->setRgbColorIdx((Lpf2::ColorIDX)mp_obj_get_int(idx));
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_PORT_METHOD_VAR_BETWEEN(set_rgb_color,
{
    void *self_in = MP_OBJ_TO_PTR(args[0]);

    uint8_t r = (uint8_t)mp_obj_get_int(args[1]);
    uint8_t g = (uint8_t)mp_obj_get_int(args[2]);
    uint8_t b = (uint8_t)mp_obj_get_int(args[3]);
    GET_SELF_CPP()->setRgbColor(r, g, b);
    return mp_const_none;
},
4, 4);

DEFINE_PORT_METHOD(set_mode, (mp_obj_t self_in, mp_obj_t mode)
{
    int ret = GET_SELF_CPP()->setMode(mp_obj_get_int(mode));
    return mp_obj_new_int(ret);
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_PORT_METHOD(set_mode_combo, (mp_obj_t self_in, mp_obj_t idx)
{
    int ret = GET_SELF_CPP()->setModeCombo(mp_obj_get_int(idx));
    return mp_obj_new_int(ret);
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_PORT_METHOD(is_device_connected, (mp_obj_t self_in)
{
    return mp_obj_new_bool(GET_SELF_CPP()->isDeviceConnected());
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_PORT_METHOD(get_value, (mp_obj_t self_in, mp_obj_t mode, mp_obj_t dataSet)
{
    float ret = GET_SELF_CPP()->getValue((uint8_t)mp_obj_get_int(mode), (uint8_t)mp_obj_get_int(dataSet));
    return mp_obj_new_float(ret);
},
MP_DEFINE_CONST_FUN_OBJ_3);

DEFINE_PORT_METHOD(get_value_str, (mp_obj_t self_in, mp_obj_t mode)
{
    std::string s = GET_SELF_CPP()->getValueStr((uint8_t)mp_obj_get_int(mode));
    return mp_obj_new_str(s.c_str(), s.length());
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_PORT_METHOD(get_device_type, (mp_obj_t self_in)
{
    return mp_obj_new_int((int)GET_SELF_CPP()->getDeviceType());
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_PORT_METHOD(get_mode_count, (mp_obj_t self_in)
{
    return mp_obj_new_int(GET_SELF_CPP()->getModeCount());
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_PORT_METHOD(get_view_count, (mp_obj_t self_in)
{
    return mp_obj_new_int(GET_SELF_CPP()->getViewCount());
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_PORT_METHOD(get_mode, (mp_obj_t self_in, mp_obj_t num)
{
    auto self = GET_SELF_CPP();
    auto& modes = self->getModes();
    uint8_t modeNum = mp_obj_get_int(num);
    if (modeNum >= modes.size())
    {
        return mp_const_none;
    }
    mp_obj_lpf2_mode_t *mode = (mp_obj_lpf2_mode_t*)m_malloc_with_finaliser(sizeof(mp_obj_lpf2_mode_t));
    mode->base.type = &lpf2_mode_type;
    mode->cpp_obj = new Lpf2::Mode(modes[modeNum]);
    mode->owned = true; // owned by the mode
    return MP_OBJ_FROM_PTR(mode);
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_PORT_METHOD(get_mode_combo_count, (mp_obj_t self_in)
{
    return mp_obj_new_int(GET_SELF_CPP()->getModeComboCount());
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_PORT_METHOD(get_mode_combo, (mp_obj_t self_in, mp_obj_t combo)
{
    return mp_obj_new_int(GET_SELF_CPP()->getModeCombo((uint8_t)mp_obj_get_int(combo)));
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_PORT_METHOD(get_input_modes, (mp_obj_t self_in)
{
    return mp_obj_new_int(GET_SELF_CPP()->getInputModes());
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_PORT_METHOD(get_output_modes, (mp_obj_t self_in)
{
    return mp_obj_new_int(GET_SELF_CPP()->getOutputModes());
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_PORT_METHOD(get_capabilities, (mp_obj_t self_in)
{
    return mp_obj_new_int(GET_SELF_CPP()->getCapabilities());
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_PORT_METHOD(get_info_str, (mp_obj_t self_in)
{
    std::string s = GET_SELF_CPP()->getInfoStr();
    return mp_obj_new_str(s.c_str(), s.length());
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_PORT_METHOD(get_port_num, (mp_obj_t self_in)
{
    return mp_obj_new_int((uint8_t)GET_SELF_CPP()->getPortNum());
},
MP_DEFINE_CONST_FUN_OBJ_1);

DEFINE_PORT_METHOD(speed_to_raw, (mp_obj_t self_in, mp_obj_t speed)
{
    return mp_obj_new_int((int)Lpf2::Port::speedToRaw((int8_t)mp_obj_get_int(speed)));
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_PORT_METHOD(raw_to_speed, (mp_obj_t self_in, mp_obj_t raw)
{
    return mp_obj_new_int((int)Lpf2::Port::rawToSpeed((uint8_t)mp_obj_get_int(raw)));
},
MP_DEFINE_CONST_FUN_OBJ_2);

DEFINE_PORT_METHOD(del, (mp_obj_t self_in)
{
    auto self = GET_SELF();
    LPF2_LOG_V("Deleting Port, owner: %s", self->owned ? "true" : "false");
    if (self->owned)
    {
        delete self->cpp_obj;
        self->cpp_obj = nullptr;
    }
    return mp_const_none;
},
MP_DEFINE_CONST_FUN_OBJ_1);

static const mp_rom_map_elem_t lpf2_port_locals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___del__), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(del))},
    {MP_ROM_QSTR(MP_QSTR_writeData), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(write_data))},
    {MP_ROM_QSTR(MP_QSTR_startPower), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(start_power))},
    {MP_ROM_QSTR(MP_QSTR_setAccTime), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(set_acc_time))},
    {MP_ROM_QSTR(MP_QSTR_setDecTime), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(set_dec_time))},
    {MP_ROM_QSTR(MP_QSTR_startSpeed), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(start_speed))},
    {MP_ROM_QSTR(MP_QSTR_startSpeedForTime), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(start_speed_for_time))},
    {MP_ROM_QSTR(MP_QSTR_startSpeedForDegrees), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(start_speed_for_degrees))},
    {MP_ROM_QSTR(MP_QSTR_gotoAbsPosition), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(goto_abs_pos))},
    {MP_ROM_QSTR(MP_QSTR_presetEncoder), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(preset_encoder))},
    {MP_ROM_QSTR(MP_QSTR_setRgbColorIdx), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(set_rgb_color_idx))},
    {MP_ROM_QSTR(MP_QSTR_setRgbColor), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(set_rgb_color))},
    {MP_ROM_QSTR(MP_QSTR_setMode), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(set_mode))},
    {MP_ROM_QSTR(MP_QSTR_setModeCombo), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(set_mode_combo))},
    {MP_ROM_QSTR(MP_QSTR_isDeviceConnected), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(is_device_connected))},
    {MP_ROM_QSTR(MP_QSTR_getValue), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_value))},
    {MP_ROM_QSTR(MP_QSTR_getValueStr), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_value_str))},
    {MP_ROM_QSTR(MP_QSTR_getDeviceType), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_device_type))},
    {MP_ROM_QSTR(MP_QSTR_getModeCount), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_mode_count))},
    {MP_ROM_QSTR(MP_QSTR_getViewCount), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_view_count))},
    {MP_ROM_QSTR(MP_QSTR_getMode), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_mode))},
    {MP_ROM_QSTR(MP_QSTR_getModeComboCount), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_mode_combo_count))},
    {MP_ROM_QSTR(MP_QSTR_getModeCombo), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_mode_combo))},
    {MP_ROM_QSTR(MP_QSTR_getInputModes), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_input_modes))},
    {MP_ROM_QSTR(MP_QSTR_getOutputModes), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_output_modes))},
    {MP_ROM_QSTR(MP_QSTR_getCapabilities), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_capabilities))},
    {MP_ROM_QSTR(MP_QSTR_getInfoStr), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_info_str))},
    {MP_ROM_QSTR(MP_QSTR_getPortNum), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(get_port_num))},
    {MP_ROM_QSTR(MP_QSTR_speedToRaw), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(speed_to_raw))},
    {MP_ROM_QSTR(MP_QSTR_rawToSpeed), MP_ROM_PTR(&GET_PORT_METHOD_OBJ(raw_to_speed))},
};

static MP_DEFINE_CONST_DICT(lpf2_port_locals_dict, lpf2_port_locals_table);

MP_DEFINE_CONST_OBJ_TYPE(
    lpf2_port_type, 
    MP_QSTR_port,
    MP_TYPE_FLAG_NONE,
    make_new, (void*)lpf2_port_make_new,
    locals_dict, &lpf2_port_locals_dict
);

MP_DEFINE_CONST_OBJ_TYPE(
    lpf2_local_port_type, 
    MP_QSTR_local_port,
    MP_TYPE_FLAG_NONE,
    parent, &lpf2_port_type,
    locals_dict, &lpf2_port_locals_dict
);
} // extern "C"