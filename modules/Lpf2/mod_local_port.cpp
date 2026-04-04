extern "C" {
#include "py/runtime.h"
}

#include "mod_types.h"

#define SELF_TYPE mp_obj_lpf2_local_port_t

extern "C" {
static mp_obj_t lpf2_local_port_set_power(mp_obj_t self_in,
                                          mp_obj_t p1_in,
                                          mp_obj_t p2_in) {
    GET_SELF_CPP()->setPower(
        mp_obj_get_int(p1_in),
        mp_obj_get_int(p2_in)
    );

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_3(lpf2_local_port_set_power_obj, lpf2_local_port_set_power);

static mp_obj_t lpf2_local_port_device_connected(mp_obj_t self_in) {
    return mp_obj_new_bool(GET_SELF_CPP()->deviceConnected());
}
static MP_DEFINE_CONST_FUN_OBJ_1(lpf2_local_port_device_connected_obj, lpf2_local_port_device_connected);

static mp_obj_t lpf2_local_port_write_data(mp_obj_t self_in,
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
}
static MP_DEFINE_CONST_FUN_OBJ_3(lpf2_local_port_write_data_obj, lpf2_local_port_write_data);

static const mp_rom_map_elem_t lpf2_local_port_locals_table[] = {
    {MP_ROM_QSTR(MP_QSTR_setPower), MP_ROM_PTR(&lpf2_local_port_set_power_obj)},
    {MP_ROM_QSTR(MP_QSTR_deviceConnected), MP_ROM_PTR(&lpf2_local_port_device_connected_obj)},
    {MP_ROM_QSTR(MP_QSTR_writeData), MP_ROM_PTR(&lpf2_local_port_write_data_obj)},
};

static MP_DEFINE_CONST_DICT(lpf2_local_port_locals_dict, lpf2_local_port_locals_table);

MP_DEFINE_CONST_OBJ_TYPE(
    lpf2_local_port_type, 
    MP_QSTR_local_port,
    MP_TYPE_FLAG_NONE,
    parent, &lpf2_port_type,
    locals_dict, &lpf2_local_port_locals_dict
);
} // extern "C"