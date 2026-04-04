#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "py/obj.h"

mp_obj_t mp_bridge_obj_new_int(int v);
mp_obj_t mp_bridge_obj_new_bytes(const byte *data, size_t len);
mp_obj_t mp_bridge_obj_new_bool(mp_int_t x);
mp_int_t mp_bridge_obj_get_int(mp_const_obj_t arg);
bool mp_bridge_obj_is_true(mp_obj_t arg);

mp_obj_t mp_bridge_call_function_n_kw(mp_obj_t fun, size_t n, size_t kw, const mp_obj_t *args);
mp_obj_t mp_bridge_call_function_0(mp_obj_t fun);
mp_obj_t mp_bridge_call_function_1(mp_obj_t fun, mp_obj_t arg);

mp_obj_t mp_bridge_load_attr(mp_obj_t obj, qstr attr);

void mp_bridge_get_buffer_raise(mp_obj_t obj, mp_buffer_info_t *bufinfo, mp_uint_t flags);

#ifdef __cplusplus
}
#endif